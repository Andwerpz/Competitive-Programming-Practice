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

//Codeforces - 1527D

//when asked to compute for each x the number of structures that have some property equal to x, alot of the times it's
//easier to compute the amount of structures that have property >= x, and then take the differences. 

//we can do a few cases:
//mex >= 0 : this is just every path in the tree, so n * (n - 1) / 2
//mex >= 1 : this is every path in the tree that includes 0. 
//mex >= i, i >= 2 : all of these have to include 2 or more nodes, so they'll all include some 'line' in the tree.
//  can solve this case using LCA, binary lifting, and some casework.  

//single modify, range query
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
            c[u].push_back(v);
            c[v].push_back(u);
        }
        LCA lca(n, 0, c);
        vl ans(n + 1, 0);
        vi sz(n, 1);
        const int B = 20;
        vvi bl(n, vi(B, 0));
        function<int(int, int)> dfs_sz = [&](int cur, int p) -> int {
            bl[cur][0] = p;
            for(int& x : c[cur]) if(x != p) sz[cur] += dfs_sz(x, cur);
            return sz[cur];
        };
        dfs_sz(0, -1);
        for(int i = 1; i < B; i++){ 
            for(int j = 0; j < n; j++){
                if(bl[j][i - 1] != -1) bl[j][i] = bl[bl[j][i - 1]][i - 1];
            }
        }
        function<int(int, int)> kth_par = [&](int ind, int k) -> int {
            int ans = ind;
            for(int i = 0; i < B; i++){
                if(k & (1 << i) && ans != -1) ans = bl[ans][i];
            }
            return ans;
        };
        //returns the first node on the path from na -> nb
        function<int(int, int)> first_to = [&](int na, int nb) -> int {
            if(lca.lca(na, nb) == na) {
                //have to go down
                return kth_par(nb, lca.depth[nb] - lca.depth[na] - 1);
            }
            //have to go up
            return bl[na][0];
        };
        //for now, ans[i] = how many paths have mex >= i
        //mex = 0, everything
        ans[0] = (ll) n * (ll) (n - 1) / 2;
        //mex = 1, just have to contain 0
        ans[1] = (ll) (n - 1) * (ll) (n - 2) / 2;
        for(int& x : c[0]) ans[1] -= (ll) sz[x] * (ll) (sz[x] - 1) / 2;
        ans[1] += n - 1;
        //mex > 1, have to contain some 'line' of nodes
        int e0 = 0, e1 = 0;
        for(int i = 1; i < n; i++){
            //we have two cases, is e0 an ancestor of e1 or not. 
            if(lca.lca(e0, e1) == e1) {
                //the line goes from e0 up to e1. 
                if(lca.lca(e0, i) == e0) {  //extends below e0
                    e0 = i;
                    goto notdone;
                }
                if(lca.lca(e1, i) != e1) {   //extends above e1
                    e1 = i;
                    goto notdone;
                }
                if(lca.lca(e0, i) == i && lca.lca(e1, i) == e1) {   //on line
                    goto notdone;
                }
                if(lca.lca(first_to(e1, e0), i) != first_to(e1, e0)) {    //extends below e1
                    e1 = i;
                    goto notdone;
                }
            }
            else {
                //the line goes from e0 up to lca(e0, e1) then back down to e1
                //see if i extends the line
                if(lca.lca(e0, i) == e0) {
                    e0 = i;
                    goto notdone;
                }
                if(lca.lca(e1, i) == e1) {
                    e1 = i;
                    goto notdone;
                }
                //see if i falls on the line
                if((lca.lca(e0, i) == i || lca.lca(e1, i) == i) && lca.lca(lca.lca(e0, e1), i) != i) {
                    goto notdone;
                }
            }
            //rip
            break;
            notdone: {}
            //compute the answer
            if(lca.lca(e0, e1) == e1) {
                ll e1cnt = (n - sz[first_to(e1, e0)]);
                ans[i + 1] = (ll) sz[e0] * e1cnt;
                // cout << "E1 ancestor of E0\n";
                // cout << sz[e0] << " " << e1cnt << "\n";
            }
            else {
                ans[i + 1] = (ll) sz[e0] * (ll) sz[e1];
                // cout << "E1 not ancestor of E0\n";
                // cout << sz[e0] << " " << sz[e1] << "\n";
            }
        }
        // for(int i = 0; i <= n; i++) cout << ans[i] << " ";
        // cout << "\n";
        ll sum = 0;
        for(int i = n; i >= 0; i--){
            ans[i] -= sum;
            sum += ans[i];
        }
        for(int i = 0; i <= n; i++) cout << ans[i] << " \n"[i == n];
    }
    
    return 0;
}