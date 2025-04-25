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

//Spring 2025 Columbia University Local Contest - D

//observe that if we had some all pairs shortest paths computed, then we can use that to directly compute the answer
//O(n^3) is good enough with good constant factor, so use floyd warshall. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, _k;
        cin >> n >> m >> _k;
        vector<vector<pii>> c(n + m);
        for(int i = 0; i < _k; i++){
            int u, v, cost;
            cin >> u >> v >> cost;
            c[u].push_back({v, cost});
            c[v].push_back({u, cost});
        }
        vvl dist(n + m, vl(n + m, 1e18));
        for(int i = 0; i < n + m; i++){
            dist[i][i] = 0;
            for(pii& x : c[i]) dist[i][x.first] = x.second;
        }
        for(int i = 0; i < n + m; i++){
            for(int j = 0; j < n + m; j++){
                for(int k = 0; k < n + m; k++){
                    if(dist[j][k] > dist[j][i] + dist[i][k]) dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
        ll ans = 1e18, ansind = -1;
        for(int i = n; i < n + m; i++){
            ll cans = 0;
            bool is_valid = true;
            for(int j = 0; j < n; j++){
                if(dist[i][j] == 1e18) {
                    is_valid = false;
                    break;
                }
                cans += dist[i][j];
            }   
            if(is_valid) if(ans > cans) ans = cans, ansind = i;
        }
        if(ans == 1e18) cout << "-1\n";
        else cout << ansind << " " << ans << "\n";
    }
    
    return 0;
}