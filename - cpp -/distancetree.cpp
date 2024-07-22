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

//Codeforces - 1632 E1, E2

//my solution is like 300 lines while the editorial has a 50 line solution D:
//i'll be explaining the editorial solution, mine is too convoluted. 

//we can go ahead and root the tree at node 1, since we only care about distances to that node. 
//first thing to notice is that the edge you add should always be connected to node 1. This is true because you can
//always shorten the distance by connecting the edge to node 1 if it isn't already there. 

//now, lets try to make the answer at most ans. For any node initially less or equal to ans distance away from 1, 
//we can ignore those, because they don't need fixing. For every other node however, their new shortest path to node
//1 should be able to travel through the edge we're about to add. 

//consider the longest path between any two nodes with depth greater than ans. Our edge should connect to the 
//midpoint of this path, as it should try to minimize the maximum distance. From here, we can easily check if the
//answer is greater than ans. 

//we can precompute the diameters for every ans in O(n * log(n)) time using LCA, and then we can use 2 pointers or 
//binary search to generate the answers for every x. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
        }
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++){
            t[i + n] = arr[i];
        }
        build();
    }

    void build() { // build the tree after manually assigning the values.
        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none) {
            return r_res;
        }
        if(r_none) {
            return l_res;
        }
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

struct RMQ  {
    vector<int> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    int *mask, *sparse_table;
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int least_significant_bit(int x) {return x & -x;}
    int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
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
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    int query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
        if(r - l + 1 <= block_size) return small_query(r, r - l + 1);
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1;
        int y = r / block_size - 1;
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        // return elements[ans]; //return the value
        return ans;        //return the index with value
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

    void euler_tour(int cur, int p, vector<int>& depth, vector<int>& ret) {
        left_occ[cur] = ret.size();
        ret.push_back(cur);
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            euler_tour(next, cur, depth, ret);
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

        this->tour = vector<int>(0);
        this->left_occ = vector<int>(n, -1);
        this->right_occ = vector<int>(n, -1);
        euler_tour(root, -1, depth, tour);
        vector<int> tourd(tour.size());
        for(int i = 0; i < tour.size(); i++){
            tourd[i] = depth[tour[i]];
        }
        rmq = RMQ(tourd);
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
            }
            edges[parents[i]].push_back(i);
            edges[i].push_back(parents[i]);
        }
        init(n, root, edges);
    }

    int lca(int a, int b) {
        int l = min(left_occ[a], left_occ[b]);
        int r = max(right_occ[a], right_occ[b]);
        int lc = rmq.query(l, r - 1);
        return tour[lc];
    }

    int dist(int a, int b) {
        int lc = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lc];
    }
};

void dfs(int cur, int p, vvi& c, vi& depth, vi& par) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        par[next] = cur;
        depth[next] = depth[cur] + 1;
        dfs(next, cur, c, depth, par);
    }
}

void gen_tour(int cur, int p, vvi& c, vi& depth, vi& tl, vi& tr, vi& tour) {
    tl[cur] = tour.size();
    tour.push_back(depth[cur]);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        gen_tour(next, cur, c, depth, tl, tr, tour);
    }
    tr[cur] = tour.size();
}

void calc_diam(int cur, int p, vvi& c, LCA& lca, int& da, int& db, vb& v){
    if(v[cur]) {
        return;
    }
    v[cur] = true;
    if(lca.dist(cur, da) > lca.dist(da, db)) {
        db = cur;
    }
    if(lca.dist(cur, db) > lca.dist(da, db)) {
        da = cur;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        calc_diam(next, cur, c, lca, da, db, v);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
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
        vi depth(n, 0), par(n, -1);
        dfs(0, -1, c, depth, par);
        vi tl(n), tr(n), tour(0);
        gen_tour(0, -1, c, depth, tl, tr, tour);
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        Segtree<int> segt(n, 0, -1e9, fmodify, fcombine);
        segt.assign(tour);
        int maxd = 0, maxv;
        for(int i = 1; i < n; i++){
            if(depth[i] > depth[maxd]) {
                maxd = i;
            }
        }
        maxv = depth[maxd];
        vi path(0);
        while(par[maxd] != -1){
            path.push_back(maxd);
            maxd = par[maxd];
        }
        vi out(path.size());
        vb v(n, false);
        vector<pii> diam(path.size());
        int _da = path[0], _db = path[0];
        for(int i = 0; i < path.size(); i++){
            int l = tl[path[i]];
            int r = tr[path[i]];
            out[i] = max(segt.query(0, l), segt.query(r, n));
            calc_diam(path[i], par[path[i]], c, lca, _da, _db, v);
            diam[i] = {_da, _db};
        }
        vi ans(0);
        for(int i = 1; i <= n; i++){
            int low = 1;
            int high = maxv;
            int cans = maxv;
            while(low <= high){
                int mid = low + (high - low) / 2;
                bool is_valid = true;
                {
                    if(mid == maxv) {
                        goto done;
                    }
                    if(i > mid) {
                        is_valid = false;
                        goto done;
                    }
                    int ind = mid - i;
                    int roi = (depth[path[ind]] - i) / 2;
                    int in = 0;
                    in = max(in, lca.dist(path[ind], diam[ind + roi].first));
                    in = max(in, lca.dist(path[ind], diam[ind + roi].second));
                    in += i;
                    if(max(in, out[ind + roi]) > mid) {
                        is_valid = false;
                    }
                }
                done:
                if(is_valid) {
                    cans = min(cans, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            ans.push_back(cans);
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}