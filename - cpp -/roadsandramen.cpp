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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1434D

//claim: any longest path must end at a diameter endpoint. 

//then, if we take the above for granted, we can root the tree at a diameter endpoint. Then, we
//can analyze what happens when we toggle an edge. It simply inverts the validity of all the starting points
//in the subtree. 

//so if we maintain a segment tree over the euler tour of the tree rooted at the diameter endpoint, that can
//support range max query and negation modify, then we can process each edge flip in O(log(n)) time. 

//of course, the initial claim is nontrivial. Look at editorial for proof. 

void _find_diameter_dfs(vector<vector<pair<int, ll>>>& c, vector<ll>& dist, vector<int>& prev, int start) {
    int n = c.size();
    prev = vector<int>(n, -1);
    dist = vector<ll>(n, 1e18);
    vector<bool> v(n, false);
    queue<int> q;
    q.push(start);
    v[start] = true;
    dist[start] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll ndist = c[cur][i].second + dist[cur];
            if(!v[next]) {
                v[next] = true;
                prev[next] = cur;
                dist[next] = ndist;
                q.push(next);
            }
        }
    }
}

vector<vector<pair<int, ll>>> _find_diameter_addweight(vector<vector<int>>& c) {
    vector<vector<pair<int, ll>>> _c(c.size());
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j];
            _c[u].push_back({v, 1});
        }
    }
    return _c;
}

void _find_diameter_dfs(vector<vector<int>>& c, vector<ll>& dist, vector<int>& prev, int start) {
    vector<vector<pair<int, ll>>> _c = _find_diameter_addweight(c);
    _find_diameter_dfs(_c, dist, prev, start);
}

pair<ll, pair<int, int>> find_diameter(vector<vector<pair<int, ll>>>& c){
    vector<ll> dist; vector<int> prev;
    _find_diameter_dfs(c, dist, prev, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, dist, prev, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    ll out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}

pair<ll, pair<int, int>> find_diameter(vector<vector<int>>& c) {
    vector<vector<pair<int, ll>>> _c = _find_diameter_addweight(c);
    return find_diameter(_c);
}

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n; i++){
                t[i + n] = initVal;
            }
            build();
        }

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++){
                t[i + n] = arr[i];
            }
            build();
        }

        //build tree after manually assigning values
        void build() {
            for(int i = n - 1; i > 0; i--){
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
            return _query(ind, ind + 1, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, int k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            int mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            int mid = tl + (tr - tl) / 2;
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

void gen_tour(int cur, int p, vector<vector<pii>>& cr, vi& tour, vi& tl, vi& tr, vi& depth, bool f_depth) {
    tl[cur] = tour.size();
    tour.push_back(cur);
    for(int i = 0; i < cr[cur].size(); i++){
        int next = cr[cur][i].first;
        bool flip = cr[cur][i].second;
        if(next == p){
            continue;
        }
        depth[next] = depth[cur] + 1;
        gen_tour(next, cur, cr, tour, tl, tr, depth, f_depth ^ flip);
    }
    tr[cur] = tour.size();
    if(f_depth) {
        depth[cur] *= -1;
    }
}

vi solve(int root, vvi& r, vvi& c, vi& q, vector<vector<pii>>& cr) {
    int n = c.size();
    vi tour(0), tl(n), tr(n), depth(n, 0);
    gen_tour(root, -1, cr, tour, tl, tr, depth, false);
    //{{min, max}, whether or not to mult by -1}
    function<pair<pii, bool>(pair<pii, bool>, pair<pii, bool>)> fmodify = [](const pair<pii, bool> src, const pair<pii, bool> val) -> pair<pii, bool>{
        return {src.first, src.second ^ val.second};
    };
    function<pair<pii, bool>(pair<pii, bool>, pair<pii, bool>, int)> fmodifyk = [](const pair<pii, bool> src, const pair<pii, bool> val, const int k) -> pair<pii, bool>{
        return {src.first, src.second ^ val.second};
    };
    function<pair<pii, bool>(pair<pii, bool>, pair<pii, bool>)> fcombine = [](pair<pii, bool> a, pair<pii, bool> b) -> pair<pii, bool>{
        if(a.second) {
            a.first.first *= -1;
            a.first.second *= -1;
            swap(a.first.first, a.first.second);
        }
        if(b.second) {
            b.first.first *= -1;
            b.first.second *= -1;
            swap(b.first.first, b.first.second);
        }
        return {{min(a.first.first, b.first.first), max(a.first.second, b.first.second)}, false};
    };
    SegtreeLazy<pair<pii, bool>> segt(n, {{0, 0}, 0}, {{1e18, -1e18}, 0}, {{0, 0}, 0}, fmodify, fmodifyk, fcombine);
    {
        vector<pair<pii, bool>> init(n);
        for(int i = 0; i < n; i++){
            int ind = tl[i];
            init[ind] = {{depth[i], depth[i]}, false};
        }
        segt.assign(init);
    }
    for(int i = 0; i < n; i++){
        depth[i] = abs(depth[i]);
    }
    vi ans(q.size());
    for(int i = 0; i < q.size(); i++) {
        int u = r[q[i]][0];
        int v = r[q[i]][1];
        if(depth[u] < depth[v]) {
            swap(u, v);
        }
        segt.modify(tl[u], tr[u], {{0, 0}, true});
        ans[i] = segt.query(0, n).first.second;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi r(n), c(n);
    vector<vector<pii>> cr(n);
    for(int i = 0; i < n - 1; i++){
        int u, v, t;
        cin >> u >> v >> t;
        u --;
        v --;
        r[i] = {u, v, t};
        c[u].push_back(v);
        c[v].push_back(u);
        cr[u].push_back({v, t});
        cr[v].push_back({u, t});
    }
    int m;
    cin >> m;
    vi q(m);
    for(int i = 0; i < m; i++){
        cin >> q[i];
        q[i] --;
    }
    pii ends = find_diameter(c).second;
    vi a = solve(ends.first, r, c, q, cr), b = solve(ends.second, r, c, q, cr);
    for(int i = 0; i < m; i++){
        cout << max(a[i], b[i]) << "\n";
    }
    
    return 0;
}