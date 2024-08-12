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

//Codeforces - 2002 D1, D2

//for any valid dfs order, it needs to be 'plausible' for each node to go to the next node in the sequence. 
//if a node is not a leaf, the next node must be one of it's direct children, and if it is a leaf, the next node must
//be a direct child of one of it's ancestors, or it could also just be the last element. 

//this is actually necessary and sufficient for a sequence to be a valid dfs order. This is because any invalid
//ordering will have at least one not plausible node. (and of course every valid ordering has only plausible nodes.)

//for the easy version, it's sufficient to iterate through all ancestors of a leaf to check, but for the hard version, 
//we can use LCA to speed things up. Some node n is a child of an ancestor of a leaf l if p[n] = lca(n, l), where
//p[i] is the parent of node i. 

//we can just maintain the count of 'plausible' nodes. We only have to update the plausibility of 4 nodes per query:
//a[x], a[y], a[x - 1], and a[y - 1]. Whenever the number of plausible nodes is n, print YES. 

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

        // cout << "DONE DEPTH" << endl;

        vector<int> tour(0);
        this->left_occ = vector<int>(n, -1);
        this->right_occ = vector<int>(n, -1);
        euler_tour(root, -1, tour);

        // cout << "DONE EULER TOUR" << endl;

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

void dfs(int cur, vvi& c, vi& depth) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        depth[next] = depth[cur] + 1;
        dfs(next, c, depth);
    }
}

bool is_valid(int ind, vector<set<int>>& c_set, vi& a, vi& p, LCA& lca) {
    // cout << "IS_VALID : " << a[ind] << "\n";
    int n = p.size();
    int node = a[ind];
    if(c_set[node].size() == 0){
        // cout << "IS LEAF" << endl;
        //next has to be child of ancestor or nothing. 
        if(ind == n - 1) {
            return true;
        }
        int ptr = p[node];
        int next = a[ind + 1];
        return lca.lca(ptr, next) == p[next];
    }
    //has to be child
    if(ind == n - 1){
        return false;
    }
    return c_set[node].count(a[ind + 1]);
}

void upd_valid(int ind, int& vcnt, vb& v, vector<set<int>>& c_set, vi& a, vi& p, LCA& lca) {
    vcnt -= v[a[ind]];
    v[a[ind]] = is_valid(ind, c_set, a, p, lca);
    vcnt += v[a[ind]];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<set<int>> c_set(n);
        vvi c(n);
        vi p(n, -1);
        for(int i = 1; i < n; i++){
            cin >> p[i];
            p[i] --;
            c[p[i]].push_back(i);
            c_set[p[i]].insert(i);
        }
        LCA lca(n, p);
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vi depth(n, 0);
        dfs(0, c, depth);
        int mxd = 0;
        for(int i = 0; i < n; i++){
            mxd = max(mxd, depth[i]);
        }
        //populate sets
        map<int, int> m;
        for(int i = 0; i < n; i++) {
            m[a[i]] = i;
        }
        //compute validity
        int vcnt = 0;
        vb v(n, false);
        for(int i = 0; i < n; i++){
            v[a[i]] = is_valid(i, c_set, a, p, lca);
            vcnt += v[a[i]];
        }
        // for(int j = 0; j < n; j++){
        //     cout << v[j] << " ";
        // }
        // cout << "\n";
        for(int i = 0; i < q; i++){
            int _x, _y;
            cin >> _x >> _y;
            _x --;
            _y --;
            int x = a[_x];
            int y = a[_y];
            swap(a[_x], a[_y]);
            if(p[x] != -1){
                c_set[p[x]].erase(x);
            }
            if(p[y] != -1){
                c_set[p[y]].erase(y);
            }
            swap(m[x], m[y]);
            if(p[x] != -1){
                c_set[p[x]].insert(x);
            }
            if(p[y] != -1){
                c_set[p[y]].insert(y);
            }
            upd_valid(_x, vcnt, v, c_set, a, p, lca);
            upd_valid(_y, vcnt, v, c_set, a, p, lca);
            if(_x != 0){
                upd_valid(_x - 1, vcnt, v, c_set, a, p, lca);
            }
            if(_y != 0){
                upd_valid(_y - 1, vcnt, v, c_set, a, p, lca);
            }
            // for(int j = 0; j < n; j++){
            //     cout << v[j] << " ";
            // }
            // cout << "\n";
            cout << (vcnt == n? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}