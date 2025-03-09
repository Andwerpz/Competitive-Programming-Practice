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

//UTPC Contest 2-26-25 Div.1 - D

//normal dijkstra, sometimes just have to round up the distance depending on when you get to a node. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vl r(n), g(n);
    vector<vector<pll>> c(n);
    for(int i = 0; i < n; i++){
        cin >> r[i] >> g[i];
    }
    for(int i = 0; i < m; i++){
        int u, v, l;
        cin >> u >> v >> l;
        u --, v --;
        c[u].push_back({v, l});
        c[v].push_back({u, l});
    }
    ll ans = 1e18;
    vl d(n, 1e18);
    d[0] = 0;
    priority_queue<pll> q;
    q.push({0, 0});
    while(q.size() != 0){
        int cur = q.top().second;
        ll cdist = -q.top().first;
        q.pop();
        // cout << "CDIST : " << cdist << " " << d[cur] << " " << cur << "\n";
        if(d[cur] != cdist) continue;
        for(pll x : c[cur]) {
            int next = x.first;
            ll ndist = cdist + x.second;
            if(next == n - 1){
                ans = min(ans, ndist);
            }
            if(ndist % (r[next] + g[next]) >= r[next]) {
                ndist += (r[next] + g[next]) - (ndist % (r[next] + g[next]));
            }
            if(ndist < d[next]) {
                d[next] = ndist;
                q.push({-ndist, next});
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}