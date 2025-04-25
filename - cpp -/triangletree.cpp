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

//Codeforces - 2063E

//did some weird inclusion exclusion type stuff + small to large merging. Definitely not intended. 
//my idea is to first fix the LCA, then for every LCA, compute some upper bound on the answer. The upper bound is
//if we take all pairs of nodes within the subtree, and treat each pair as if the LCA is the fixed LCA. 

//tbh, i wrote this code while also watching youtube, so it's not the most thought out code. 

//editorial solution is to notice that for some good pair (u, v),
//f(u, v) = 2 * min(dist(u, lca), dist(v, lca)) - 1
// = 2 * min(d[u] - d[lca], d[v] - d[lca]) - 1
// = 2 * min(d[u], d[v]) - 2 * d[lca] - 1
//where d[x] is the depth of node x. We can compute sums for 2 * min(d[u], d[v]) and 2 * d[lca] - 1 seperately. 

//compute for each subtree, counts of nodes at each depth in subtree
//do this using small to large merging, O(n * log(n))?
//always should merge in O(smallset)
vi ptr;     //what array indices describe the current subtree?
vvl lcnt;   //layer count, but in reverse order. Layer 0 is last element
vvl lpfx;   //prefix array of lcnt. lpfx[i][j] = sum_{n = 0}^{j} lcnt[i][n]
vl amt;     //amt[x] = sum_{i = 0}^{lcnt.size() - 2} lcnt[x][i] * lpfx[x][i]
vl ovc;     //overcounted answer per subtree
vvi c;

ll solve(int cur, int p) {
    // cout << "SOLVE : " << cur << " " << p << endl;
    //overcount current answer. Fix this node as LCA, compute sum of answers
    int ocur = cur;
    ll ans = 0;
    vi child;
    for(int x : c[cur]) if(x != p) ans += solve(x, cur), child.push_back(ptr[x]);
    if(child.size() == 0){
        //leaf node
        ovc[cur] = 0;
        amt[cur] = 0;
        lcnt[cur].push_back(1);
        lpfx[cur].push_back(1);
    }
    else if(child.size() == 1){
        //just one child. 
        ptr[cur] = child[0];
        cur = child[0];
        ovc[cur] += amt[cur] * 2 + *lpfx[cur].rbegin();
        amt[cur] += *lpfx[cur].rbegin();
        lcnt[cur].push_back(1);
        lpfx[cur].push_back(1 + *lpfx[cur].rbegin());
    }
    else {
        //multiple children, need to sort by size
        sort(child.begin(), child.end(), [&](int a, int b) -> bool {
            return lcnt[a].size() > lcnt[b].size();
        });
        ptr[cur] = child[0];
        cur = child[0];
        // cout << "CUR : " << cur << "\n";
        int sma = lcnt[child[1]].size();
        // cout << "INIT : " << ovc[cur] << " " << amt[cur] << " " << sma << endl;
        //subtract out old stuff
        ovc[cur] += amt[cur] * 2 + *lpfx[cur].rbegin(); //adjust so that current child includes its root
        amt[cur] += *lpfx[cur].rbegin();
        for(int i = 0; i < sma; i++){
            ovc[cur] -= (i * 2 + 1) * *(lcnt[cur].rbegin() + i) * *(lpfx[cur].rbegin() + i);
            ovc[cur] += (i * 2 + 1) * *(lcnt[cur].rbegin() + i) * (*(lcnt[cur].rbegin() + i) - 1) / 2;
            amt[cur] -= *(lcnt[cur].rbegin() + i) * *(lpfx[cur].rbegin() + i);
            amt[cur] += *(lcnt[cur].rbegin() + i) * (*(lcnt[cur].rbegin() + i) - 1) / 2;
        }
        // cout << "ADJ : " << ovc[cur] << " " << amt[cur] << endl;
        //upd lcnt, lpfx, add in new stuff
        for(int i = 1; i < child.size(); i++){
            int x = child[i];
            for(int j = 0; j < lpfx[x].size(); j++){
                lcnt[cur][lcnt[cur].size() - 1 - j] += lcnt[x][lcnt[x].size() - 1 - j];
            }
        }
        for(int i = sma - 1; i >= 0; i--){
            lpfx[cur][lpfx[cur].size() - 1 - i] = lcnt[cur][lcnt[cur].size() - 1 - i];
            if(lcnt[cur].size() - 1 - i > 0) lpfx[cur][lpfx[cur].size() - 1 - i] += lpfx[cur][lpfx[cur].size() - 2 - i];
            ovc[cur] += (i * 2 + 1) * *(lcnt[cur].rbegin() + i) * *(lpfx[cur].rbegin() + i);
            ovc[cur] -= (i * 2 + 1) * *(lcnt[cur].rbegin() + i) * (*(lcnt[cur].rbegin() + i) - 1) / 2;
            amt[cur] += *(lcnt[cur].rbegin() + i) * *(lpfx[cur].rbegin() + i);
            amt[cur] -= *(lcnt[cur].rbegin() + i) * (*(lcnt[cur].rbegin() + i) - 1) / 2;
            // cout << "CALC : " << *(lcnt[cur].rbegin() + i) << " " << *(lpfx[cur].rbegin() + i) << " " << ovc[cur] << " " << (i * 2 + 1) << "\n";
        }
        //add subtree root node
        lcnt[cur].push_back(1);
        lpfx[cur].push_back(1 + *lpfx[cur].rbegin());
    }
    // cout << "INFO : " << ocur << "\n";
    // cout << ovc[cur] << " " << amt[cur] << "\n";
    // for(int i = 0; i < lpfx[cur].size(); i++) cout << lpfx[cur][i] << " ";
    // cout << "\n";
    // for(int i = 0; i < lcnt[cur].size(); i++) cout << lcnt[cur][i] << " ";
    // cout << endl;
    //increment answer by overcounting
    ans += ovc[cur];
    //fix overcounting for parent
    if(p != -1) {
        ans -= ovc[cur] + amt[cur] * 2 + *lpfx[cur].rbegin();
        // cout << "OVC ADJUST : " << ovc[cur] + amt[cur] * 2 + *lpfx[cur].rbegin() << "\n";
    }
    // cout << "ANS : " << ans << "\n";
    return ans;
}

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

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

ll solve_slow(int n) {
    ll ans = 0;
    LCA lca(n, 0, c);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int lc = lca.lca(i, j);
            if(lc == i || lc == j) continue;
            int mind = min(lca.dist(i, lc), lca.dist(j, lc));
            ans += mind * 2 - 1;
        }
    }
    return ans;
}

vvi gen_tree(int n) {
    DSU dsu(n);
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        while(true){
            int u = rand() % n, v = rand() % n;
            if(dsu.unify(u, v)) {
                c[u].push_back(v);
                c[v].push_back(u);
                break;
            }
        }
    }
    return c;
}

void solve_init(int n) {
    lcnt = vvl(n), lpfx = vvl(n);
    ovc = vl(n, -1e18), amt = vl(n, -1e18);
    ptr = vi(n);
    for(int i = 0; i < n; i++) ptr[i] = i;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        c = vvi(n);
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        solve_init(n);
        // cout << solve_slow(n) << "\n";
        cout << solve(0, -1) << "\n";
    }
    
    // int n = 1000;
    // int cnt = 0;
    // while(true) {
    //     cnt ++;
    //     cout << "CNT : " << cnt << endl;
    //     c = gen_tree(n);
    //     solve_init(n);
    //     int a = solve_slow(n), b = solve(0, -1);
    //     if(a != b) {
    //         cout << "A B : " << a << " " << b << "\n";
    //         break;
    //     }
    // }
    // for(int i = 0; i < n; i++){
    //     for(int x : c[i]) {
    //         if(x > i) cout << i + 1 << " " << x + 1 << "\n";
    //     }
    // }

    return 0;
}