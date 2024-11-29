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

//USACO 2018 February Contest, Platinum - Problem 2

//can just use some facts about tree diameter + union find. 
//implementation is a pain though. 

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

LCA lca;
struct DSU {
    int N;
    vector<int> dsu;
    vector<pii> diam;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->diam = vector<pii>(n);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            diam[i] = {i, i};
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_mx_dist(int a) {
        int r = find(a);
        return max(lca.dist(a, diam[r].first), lca.dist(a, diam[r].second));
    }

    int get_diam(int a){
        int r = find(a);
        return lca.dist(diam[r].first, diam[r].second);
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        int a1 = diam[ra].first;
        int a2 = diam[ra].second;
        int b1 = diam[rb].first;
        int b2 = diam[rb].second;
        if(get_diam(ra) < lca.dist(a1, b1)) {
            diam[ra] = {a1, b1};
        }
        if(get_diam(ra) < lca.dist(a1, b2)) {
            diam[ra] = {a1, b2};
        }
        if(get_diam(ra) < lca.dist(a2, b1)) {
            diam[ra] = {a2, b1};
        }
        if(get_diam(ra) < lca.dist(a2, b2)) {
            diam[ra] = {a2, b2};
        }
        if(get_diam(ra) < lca.dist(b1, b2)) {
            diam[ra] = {b1, b2};
        }
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    // freopen("--in--.txt", "r", stdin);
    // freopen("--out--.txt", "w", stdout);

    int q, n;
    cin >> q;
    n = 0;
    vector<pair<string, int>> a(q);
    for(int i = 0; i < q; i++){
        cin >> a[i].first >> a[i].second;
        n += a[i].first == "B";
        a[i].second --;
    }
    vvi c(n);
    int ptr = 1;
    for(int i = 1; i < q; i++){
        if(a[i].first == "B" && a[i].second >= 0) {
            int u = ptr;
            int v = a[i].second;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        ptr += a[i].first == "B";
    }
    n ++;
    c.push_back({});
    //find connected components, and form full graph
    vb _v(n, false);
    for(int i = 0; i < n - 1; i++){
        if(_v[i]) continue;
        queue<int> q;
        _v[i] = true;
        q.push(i);
        vi cg;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            cg.push_back(cur);
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(!_v[next]){
                    _v[next] = true;
                    q.push(next);
                }
            }
        }
        c[n - 1].push_back(i);
        c[i].push_back(n - 1);
    }
    lca = LCA(n, 0, c);
    DSU dsu(n);
    ptr = 1;
    for(int i = 1; i < q; i++){
        if(a[i].first == "Q") {
            cout << dsu.get_mx_dist(a[i].second) << "\n";
        }
        else {
            if(a[i].second >= 0) {
                int u = ptr;
                int v = a[i].second;
                dsu.unify(u, v);
            }
            ptr ++;
        }
    }
    
    return 0;
}