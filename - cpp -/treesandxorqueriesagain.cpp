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

//Codeforces - 1902F

//apparently HLD wasn't the intended solution, and the extra log(n) factor is causing the TLE
//intended solution has O((n + q)*B^2) time complexity, where B is the number of bits. 

//ok, did the intended solution and it's much better than whatever I was doing. Much easier to implement
//as well. 

//let's arbitrarily root the tree, and note that any path in the tree can be broken up into two vertical
//paths in the rooted tree. Our goal is to find the basis for each of those paths then combine them. 

//we can first do some precomputation. For each node, we'll record the nodes that form the basis for the
//path from it to the root. However, we also want to make sure that the nodes we store are as far away as 
//possible from the root. 

//We can do this for every node in O(n * B^2), where B is the max number of bits in a[i]. For each node, 
//start building it's own basis by adding itself. Then, look at the list of it's parent, and add the nodes
//one by one, starting from the closest node. 

//to answer queries, we can just find the length of the two vertical paths using LCA, and then add in all 
//basis nodes within the given distance. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

struct LCA {
    int n;
    int root;
    vector<vector<int>> edges;
    vector<int> depth;  //distance of each node from the root

    vector<int> left_occ, right_occ;   //leftmost and rightmost occurrences for each node in the euler tour
    
    //single assignment modify, range min query
    //stores the euler tour of the tree to compute lca
    Segtree<pii> segt;

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
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            depth[next] = depth[cur] + 1;
            find_depth(next, cur);
        }
    }

    void init(int n, int root, vector<vector<int>>& edges) {
        this->n = n;
        this->root = root;
        this->edges = edges;

        this->depth = vector<int>(n, 0);
        find_depth(root, -1);

        vector<int> tour(0);
        this->left_occ = vector<int>(n, -1);
        this->right_occ = vector<int>(n, -1);
        euler_tour(root, -1, tour);

        function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{return val;};
        function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{return a.first < b.first? a : b;};
        this->segt = Segtree<pii>(tour.size(), {0, 0}, {1e9, -1}, fmodify, fcombine);
        for(int i = 0; i < tour.size(); i++){
            segt.t[i + tour.size()] = {depth[tour[i]], tour[i]};
        }
        segt.build();
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
        int l = min(left_occ[a], left_occ[b]);
        int r = max(right_occ[a], right_occ[b]);
        int lc = segt.query(l, r).second;
        return lc;
    }

    int dist(int a, int b) {
        int lc = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lc];
    }
};

const int N = 2e5 + 10;
int a[N];
vi l[N], d[N];

bool insertBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++){
        if((x & 1 << i) == 0) continue;
        if(!basis[i]) {basis[i] = x; return true;}
        x ^= basis[i];
    }
    return false;
}

bool inBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++)
        if(x & 1 << i) x ^= basis[i];
    return x == 0;
}

void dfs(int cur, int p, vvi& c) {
    // cout << "DFS : " << cur << " " << p << endl;
    vi b = vi(20, 0);
    insertBasis(b, a[cur]);
    l[cur].push_back(a[cur]);
    d[cur].push_back(0);
    if(p != -1) {
        for(int i = 0; i < d[p].size(); i++){
            if(insertBasis(b, l[p][i])) {
                l[cur].push_back(l[p][i]);
                d[cur].push_back(d[p][i] + 1);
            }
        }
    }
    for(int x : c[cur]) if(x != p) dfs(x, cur, c);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    LCA lca(n, 0, c);
    dfs(0, -1, c);
    // cout << "DONE DFS" << endl;
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int x, y, k;
        cin >> x >> y >> k;
        x --, y --;
        vi b(20, 0);
        int lc = lca.lca(x, y);
        int dx = lca.dist(x, lc), dy = lca.dist(y, lc);
        for(int j = 0; j < d[x].size(); j++){
            if(d[x][j] <= dx) insertBasis(b, l[x][j]);
        }
        for(int j = 0; j < d[y].size(); j++) {
            if(d[y][j] <= dy) insertBasis(b, l[y][j]);
        }
        cout << (inBasis(b, k)? "YES" : "NO") << "\n";
    }
    
    return 0;
}
