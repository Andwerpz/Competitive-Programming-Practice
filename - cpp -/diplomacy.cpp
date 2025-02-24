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

//2014 NAIPC - C

//bruh, check input reading next time. 

//the graph given is bipartite (kinda, each node is assigned one color)
//optimal strat is to just toggle one person always, can just brute force to find best person to toggle.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    while(true){
        int n, m;
        cin >> n >> m;
        if(n == 0) break;
        vi p(n);
        for(int i = 0; i < n; i++) cin >> p[i];
        vvi c(n);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --, v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            // cout << "I : " << i << "\n";
            int cans = 0;
            priority_queue<pii> q;  //{-dist, ind}
            vi d(n, 1e9);
            vb v(n, false);
            d[i] = 0;
            q.push({0, i});
            while(q.size() != 0){
                int cur = q.top().second;
                int dist = -q.top().first;
                q.pop();
                if(v[cur]) continue;
                if(d[cur] != dist) continue;
                v[cur] = true;
                cans = max(cans, dist);
                // cout << "CDIST : " << cur << " " << dist << "\n";
                for(int x : c[cur]) {
                    int nd = dist + (p[cur] != p[x]);
                    if(v[x]) continue;
                    if(nd >= d[x]) continue;
                    d[x] = nd;
                    q.push({-nd, x});
                }
            }
            // cout << "CANS : " << cans << "\n";
            ans = min(ans, cans);
        }
        cout << ans << "\n";
        break;
    }

    return 0;
}