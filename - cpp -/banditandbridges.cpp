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

// UTPC 10-1-25 Div1 - D H

//this only solves D, to solve H, just do this solution but add on CHT for faster transitions. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k, m;
    cin >> n >> k >> m;
    vl l(n + 2);
    l[0] = 0;
    l[n + 1] = m + 1;
    for(int i = 1; i <= n; i++) cin >> l[i];
    vector<vector<pll>> b(n + 2);   //{x, debuff}
    vector<vector<ll>> dp(n + 2);  //tot dist
    b[0].push_back({0, 1});
    b[n + 1].push_back({0, 0});
    dp[0].push_back(0);
    dp[n + 1].push_back(1e18);
    for(int i = 0; i < k; i++) {
        ll x, y, d;
        cin >> x >> y >> d;
        b[y].push_back({x, d});
        dp[y].push_back(1e18);
    }
    // cout << "HERE" << endl;
    for(int i = 0; i <= n; i++) {
        // cout << "I : " << i << endl;
        for(int j = 0; j < dp[i].size(); j++) {
            ll cd = b[i][j].second;
            ll cx = b[i][j].first;
            ll cy = l[i];
            // cout << "CD : " << cd << " " << cx << " " << cy << "\n";
            for(int k = 0; k < dp[i + 1].size(); k++) {
                ll nx = b[i + 1][k].first;
                ll ny = l[i + 1];
                dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + cd * (ll) abs(cx - nx) * (ll) abs(cy - ny));
            }
        }
    }
    cout << dp[n + 1][0] << "\n";
    
    return 0;
}