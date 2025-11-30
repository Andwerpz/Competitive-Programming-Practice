#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Meta Hacker Cup 2025 Round 3 - D

// A[i] = sum of distances of pairs with gcd a multiple of i
// B[i] = sum of distances of pairs with gcd equal to i
// B[i] = A[i] - \sum_{i|x} B[x]

// how to compute A[1]?
// for each edge, its contribution is the product of the number of nodes on either side

// how to compute A[i]?
// for each edge, its contribution is the product of the number of nodes x such that i|x on either side

// if we root the tree, we just have to count the number of nodes with gcd = i in each subtree, and compare to the total

// sqrt decomp? 
// for i < sqrt(N), do with edges so O(N) for each i
// for i > sqrt(N), do with nodes so O((N / i)^2) for each i...

// \sum_{i = sqrt(N)}^{N} (N / i)^2 = O(N * sqrt(N))

// however, distance queries between two nodes costs O(log(N))?
// perhaps with RMQ can shrink that down to O(1)

struct RMQ  {
    vector<int> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    int *mask, *sparse_table;
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int lsb(int x) {return x & -x;}
    int msbi(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - msbi(mask[r] & ((1<<size)-1));}
    RMQ() {} //need this to satisfy master goon's requirements
    RMQ (const vector<int>& input) {build(input);}
    void build (const vector<int>& input) {
        elements = input;
        n = input.size();
        mask = new int[n];
        sparse_table = new int[n];
        memset(mask, 0, n);
        memset(sparse_table, 0, n);
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            while(curr_mask > 0 && op(i, i - msbi(lsb(curr_mask))) == i) curr_mask ^= lsb(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    int _query(int l, int r) {  //queries range [l, r]
        if(r - l + 1 <= block_size) {
            return small_query(r, r - l + 1);
        }
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1;
        int y = r / block_size - 1;
        if(x <= y) {
            int j = msbi(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return ans;
    }
    int query(int l, int r) {   //queries range [l, r)
        r --;
        return _query(l, r);              //return the index with minimum value
        // return elements[_query(l, r)];      //return the minimum value
    }
};

struct LCA {
    int n;
    int root;
    vector<vector<int>> edges;
    vector<int> depth;  //distance of each node from the root

    vector<int> left_occ, right_occ;   //leftmost and rightmost occurrences for each node in the euler tour
    
    vector<int> tour;
    RMQ rmq;

    void euler_tour(int cur, int p, vector<int>& ret) {
        left_occ[cur] = ret.size();
        ret.push_back(cur);
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            euler_tour(next, cur, ret);
            ret.push_back(cur);
        }
        right_occ[cur] = ret.size();
    }

    void find_depth(int cur, int p) {
        // cout << "FIND DEPTH : " << cur << " " << p << endl;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            // cout << "NEXT : " << next << endl;
            depth[next] = depth[cur] + 1;
            find_depth(next, cur);
        }
    }

    void init(int n, int root, vector<vector<int>>& edges) {
        this->n = n;
        this->root = root;
        this->edges = edges;

        // cout << "HERE" << endl;

        this->depth = vector<int>(n, 0);
        find_depth(root, -1);

        // cout << "DONE DEPTH" << endl;

        this->tour = vi(0);
        this->left_occ = vector<int>(n, -1);
        this->right_occ = vector<int>(n, -1);
        euler_tour(root, -1, tour);

        // cout << "DONE TOUR" << endl;

        {
            vi rmqa(tour.size());
            for(int i = 0; i < tour.size(); i++) rmqa[i] = depth[tour[i]];
            rmq = RMQ(rmqa);
        }

        // function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{return val;};
        // function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{return a.first < b.first? a : b;};
        // this->segt = Segtree<pii>(tour.size(), {0, 0}, {1e9, -1}, fmodify, fcombine);
        // for(int i = 0; i < tour.size(); i++){
        //     segt.t[i + tour.size()] = {depth[tour[i]], tour[i]};
        // }
        // segt.build();
    }

    LCA() {}

    //adjacency list constructor
    LCA(int n, int root, vector<vector<int>> edges) {
        init(n, root, edges);
    }

    //parent list constructor
    //if node i is the root, then parents[i] must equal -1
    LCA(int n, vector<int> parents) {
        int root = -1;
        vector<vector<int>> edges(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            if(parents[i] == -1){
                root = i;
                continue;
            }
            edges[parents[i]].push_back(i);
            edges[i].push_back(parents[i]);
        }
        init(n, root, edges);
    }

    int lca(int a, int b) {
        // cout << "LCA : " << a << " " << b << endl;
        int l = min(left_occ[a], left_occ[b]);
        int r = max(right_occ[a], right_occ[b]);
        // cout << "L R : " << l << " " << r << " " << tour.size() << endl;
        // cout << "QUERY : " << rmq.query(l, r) << endl;
        return tour[rmq.query(l, r)];
    }

    int dist(int a, int b) {
        int lc = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lc];
    }
};

ll dfs(int cur, int p, vvi& c, vl& subt, ll tot, int val) {
    ll ans = 0;
    subt[cur] = ((cur + 1) % val) == 0;
    for(int x : c[cur]) {
        if(x == p) continue;
        ans += dfs(x, cur, c, subt, tot, val);
        subt[cur] += subt[x];
    }
    ans += subt[cur] * (tot - subt[cur]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("treehouse_telegram_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        int n;
        cin >> n;
        vvi c(n);
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int SN = sqrt(n);
        // int SN = 1;
        vl A(n + 1, 0);
        LCA lca(n, 0, c);
        vvi d(n + 1);
        for(int i = 1; i <= n; i++) {
            for(int j = i; j <= n; j += i) {
                d[i].push_back(j);
            }
        }
        for(int i = 1; i < SN; i++) {
            vl subt(n, 0);
            A[i] = dfs(0, -1, c, subt, n / i, i);
        }
        for(int i = SN; i <= n; i++) {
            if(i * 2 > n) break;
            for(int j = 0; j < d[i].size(); j++) {
                for(int k = j + 1; k < d[i].size(); k++) {
                    // cout << "GET DIST : " << d[i][j] << " " << d[i][k] << endl;
                    A[i] += lca.dist(d[i][j] - 1, d[i][k] - 1);
                    // cout << "DONE GET DIST" << endl;
                }
            }
        }
        vl B(n + 1, 0);
        for(int i = n; i > 0; i--) {
            B[i] = A[i];
            for(int j = i * 2; j <= n; j += i) {
                B[i] -= B[j];
            }
        }
        cout << "Case #" << casi << ": ";
        for(int i = 1; i <= n; i++) cout << B[i] << " ";
        cout << "\n";
    }
    
    return 0;
}