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

// UTPC 10-1-25 Div1 - B

//can do dp on maximum current elixir: dp[i][j] = max current elixir at t = i where j = have we used
//the sneaky golem?

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t, e, g;
    cin >> t >> e >> g;
    vi a(t);
    for(int i = 0; i < t; i++) cin >> a[i];
    vvi dp(t + 1, vi(2, -1));
    dp[0][0] = e;
    for(int i = 0; i < t; i++){
        dp[i + 1][0] = min(e, dp[i][0] + 1 - a[i]);
        if(dp[i][0] - a[i] - g >= 0) dp[i + 1][1] = max(dp[i + 1][1], min(e, dp[i][0] + 1 -a[i] - g));
        if(dp[i][1] - a[i] >= 0) dp[i + 1][1] = max(dp[i + 1][1], min(e, dp[i][1] + 1 - a[i]));
    }
    // for(int i = 0; i <= t; i++) cout << dp[i][0] << " " << dp[i][1] << "\n";
    if(dp[t][1] != -1) cout << "YES\n";
    else cout << "NO\n";
    
    return 0;
}