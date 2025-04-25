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

//Kattis - charlesincharge

//just binary search over the maximum allowable edge weight. 

ll do_dijk(int n, vector<vector<pll>>& c, ll lim) {
    // cout << "TRY DIJK : " << lim << "\n";
    vl d(n, 1e18);
    vb v(n, false);
    priority_queue<pll> q;
    q.push({0, 0});
    d[0] = 0;
    while(q.size() != 0){
        ll cdist = -q.top().first;
        int cur = q.top().second;
        q.pop();
        if(d[cur] != cdist || v[cur]) {
            continue;
        }
        v[cur] = true;
        // cout << "CUR : " << cur << "\n";
        for(pll& x : c[cur]) {
            if(x.second > lim) continue;
            ll ndist = cdist + x.second;
            int next = x.first;
            if(d[next] <= ndist) continue;
            d[next] = ndist;
            q.push({-ndist, next});
            // cout << "PUSHQ : " << ndist << " " << next << "\n";
        }
    }
    return d[n - 1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m, x;
    cin >> n >> m >> x;
    vector<vector<pll>> c(n);
    for(int i = 0; i < m; i++){
        ll u, v, l;
        cin >> u >> v >> l;
        u --, v --;
        c[u].push_back({v, l});
        c[v].push_back({u, l});
    }
    ll base = do_dijk(n, c, 1e10);
    ll lim = (base * x + base * 100) / 100;
    // cout << "LIM : " << lim << "\n";
    ll low = 0, high = 1e10;
    ll ans = high;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        ll dist = do_dijk(n, c, mid);
        // cout << "DIST : " << dist << "\n";
        if(dist <= lim) {
            ans = mid, high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}