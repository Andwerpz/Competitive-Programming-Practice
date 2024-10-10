#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2024 ICPC Asia Pacific Championship - J

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<pair<ll, ll>>> adj(n+1);

    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    vector<ll> dp(n+1, 1e10), dp_rev(n+1, 1e10);
    vector<int> parent(n+1);

    priority_queue<pair<ll, ll>> pq;

    pq.push({0, 1});
    dp[1] = 0;
    while (pq.size()) {
        auto p = pq.top();
        pq.pop();
        ll dist = -p.first;
        int v = p.second;
        if (dp[v] != dist) {
            continue;
        }
        for (auto e : adj[v]) {
            int nei = e.first;
            ll wei = e.second;
            if (dp[nei] > (dist + wei)) {
                parent[nei] = v;
                dp[nei] = (dist + wei);
                pq.push({-(dist + wei), nei});
            }
        }
    }
    dp_rev[n] = 0;
    pq.push({0, n});
    while (pq.size()) {
        auto p = pq.top();
        pq.pop();
        ll dist = -p.first;
        int v = p.second;
        if (dp_rev[v] != dist) {
            continue;
        }
        for (auto e : adj[v]) {
            int nei = e.first;
            ll wei = e.second;
            if (dp_rev[nei] > (dist + wei)) {
                dp_rev[nei] = dist + wei;
                pq.push({-(dist + wei), nei});
            }
        }
    }
    vector<pair<ll, ll>> diverg;
    set<int> shortest;
    parent[1] = 0;
    int idx = n;
    while (idx) {
        shortest.insert(idx);
        idx = parent[idx];
    }
    ll cnt = 1e10;
    for (auto x : shortest) {
        for (auto e : adj[x]) {
            int y = e.first;
            bool works = false;

            if (shortest.count(y)) {
                if (parent[y] == x || parent[x] == y)
                    continue;
            }
            
            ll wei = e.second;
            ll alter = dp[x] + wei + dp_rev[y];
            // cerr << "x : " << x << " y : " << y << " alter : " << alter << endl;
            cnt = min(cnt, alter);
        }
    }
    // cerr 
    // cerr << "cnt : " << cnt << endl;
    cnt += dp[n];
    if (cnt >= 1e10)
        cout << -1 << endl;
    else cout << cnt << endl;

    
    return 0;
}
