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

//Codeforces - 372D

//lots of interesting ideas here.

//the core of the solution is given a set of nodes in a tree, figure out the size of the minimum
//arbitrarily connected subtree that contains all of the nodes. If we can do this quickly (supporting add
//and remove node queries), then we can easily solve the problem using a 2 pointer approach. 

//root the tree arbitrarily, then create a dfs ordering of the nodes. To add a node a to the set, find the nodes
//in the set that are just before and after a in the dfs ordering, denote them as b and c respectively. 
//if there isn't a node before or after a in the dfs ordering, 

//Then, the new size of the set is <old size> + (dist(a, b) + dist(a, c) - dist(b, c)) / 2
//intuitively, it's because dist(a, b) + dist(a, c) is double counting the distance from a to the closest node 
//within the set, and dist(b, c) represents all the path length inside of the set. 
//not exactly sure how to prove it though. 

//in the end, we can achieve log(n) addition and removal using LCA (i guess could also do O(1) using sparse table)

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

void dfs(int cur, int p, vvi& c, vi& ord, int& ptr){
    ord[cur] = ptr ++;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        dfs(next, cur, c, ord, ptr);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
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
    vi ord(n);
    {int ptr = 0; dfs(0, -1, c, ord, ptr);}
    int sz = 1;
    int r = 1;
    set<pii> s;
    s.insert({ord[0], 0});
    int ans = 0;
    for(int i = 0; i < n; i++){
        while(r != n){
            int prev = -1, next = -1;
            if(s.begin()->first < ord[r]) {
                auto ptr = s.lower_bound({ord[r], 0});
                ptr --;
                prev = ptr->second;
            }
            else {
                prev = s.rbegin()->second;
            }
            if(s.rbegin()->first > ord[r]) {
                auto ptr = s.lower_bound({ord[r], 0});
                next = ptr->second;
            }
            else {
                next = s.begin()->second;
            }
            int nsz = sz + (lca.dist(r, next) + lca.dist(r, prev) - lca.dist(next, prev)) / 2;
            if(nsz > k) break;
            sz = nsz;
            s.insert({ord[r], r});
            r ++;
        }
        ans = max(ans, r - i);
        if(r == i + 1){
            s.erase({ord[i], i});
            if(r != n){
                s.insert({ord[r], r});
                sz = 1;
                r ++;
            }
            continue;
        }
        int prev = -1, next = -1;
        s.erase({ord[i], i});
        if(s.begin()->first < ord[i]) {
            auto ptr = s.lower_bound({ord[i], 0});
            ptr --;
            prev = ptr->second;
        }
        else {
            prev = s.rbegin()->second;
        }
        if(s.rbegin()->first > ord[i]) {
            auto ptr = s.lower_bound({ord[i], 0});
            next = ptr->second;
        }
        else {
            next = s.begin()->second;
        }
        sz -= (lca.dist(i, next) + lca.dist(i, prev) - lca.dist(next, prev)) / 2;
    }
    cout << ans << "\n";
    
    return 0;
}