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

//CTU Open 2021 - B

//weird priority queue, DFS tree solution from josh. 

template <typename T> 
struct Segtree {
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this->n = n;
        t = new T[2 * n];

        this->fmodify = fmodify;
        this->fcombine = fcombine;

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

    void build() {
        for(int i = n - 1; i > 0; i--){
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) {
        p += n;
        t[p] = fmodify(t[p], value);
        for(p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) {
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for(l += n, r += n; l < r; l /= 2, r /= 2){
            if(l % 2 == 1){
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l ++;
            }
            if(r % 2 == 1){
                r --;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none){
            return r_res;
        }
        if(r_none){
            return l_res;
        }
        return fcombine(l_res, r_res);
    }

    T query(int ind){
        return this->query(ind, ind + 1);
    }
};

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     vector<ll> weis(n);
//     for (auto& x : weis)
//         cin >> x;
    
//     vector<vector<pll>> adj(n);
//     for (int i = 0; i < m; ++i) {
//         int a, b, c; cin >> a >> b >> c;
//         adj[a].push_back({b, c});
//         adj[b].push_back({a, c});
//     }
    
//     ll mn = 1e15;
//     for (int i = 0; i < n; ++i) {
//         // run dijkstras
//         priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
//         pq.push({weis[i], i});

//         bitset<10000> bit{};
        
//         while (pq.size()) {
//             auto [wei, v] = pq.top();
//             pq.pop();
            
//             if (bit[v])
//                 continue;
            
//             bit[v] = true;
            
//             for (auto [nei, e] : adj[v]) {
//                 if (bit[nei])
//                     continue;
//                 mn = min(mn, wei + e + weis[nei]);
//                 if ((wei + e) >= weis[nei])
//                     continue;
                
//                 pq.push({wei + e, nei});
//             }
//         }
//     }   

//     cout << mn << "\n";

//     return 0;
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> w(n);

    vector<vector<array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int b, c, d; cin >> b >> c >> d;
        adj[b].push_back({c,d});
        adj[c].push_back({b,d});
    }

    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector<int> vis(n,-1);
    for(int i = 0; i < n; i++) {
        pq.push({a[i],i,i});
    }

    ll res = LLONG_MAX;

    while(pq.size()) {
        auto [cost, idx, par] = pq.top();
        pq.pop();

        if(vis[idx] != -1) continue;
        vis[idx] = par;
        w[idx] = cost;

        for(auto [dest, edge_weight] : adj[idx]) {
            if(vis[dest] == -1) {
                res = min(res, cost + edge_weight + a[dest]);
            }
            if(vis[dest] != -1 && vis[idx] != vis[dest]) {
                res = min(res, cost + edge_weight + w[dest]);
            }
            pq.push({cost + edge_weight, dest, par});
        }
    }

    cout << res << '\n';

    // int n, m; cin >> n >> m;
    // vector<ll> a(n);
    // for(ll &x : a) cin >> x;

    // vector<unordered_map<ll,ll>> adj(n);
    // for(int i = 0; i < m; i++) {
    //     int b, c, d; cin >> b >> c >> d;
    //     adj[b][c] = d;
    //     adj[c][b] = d;
    // }

    // function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll{return val;};
    // function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{return a.first < b.first? a : b;};
    // Segtree<pll> segt(n, {0,0}, {LLONG_MAX, -1}, fmodify, fcombine);

    // for(int i = 0; i < n; i++) {
    //     segt.modify(i, {a[i], i});
    // }

    // vector<int> vis(n);
    // ll res = LLONG_MAX;

    // for(int i = 0; i < n; i++) {
    //     auto [w, idx] = segt.query(0,n);
    //     vis[idx] = 1;
    //     segt.modify(idx, {LLONG_MAX, idx});
    //     a[idx] = w;

    //     for(auto [child, b] : adj[idx]) {
    //         res = min(res, w + b + a[child]);
    //         if(vis[child] == 0 && w + b < segt.query(child).first) {
    //             segt.modify(child, {w+b, child});
    //         }
    //         adj[child].erase(idx);
    //     }
    //     adj[idx].clear();
    // }

    // cout << res << '\n';

    
    return 0;
}