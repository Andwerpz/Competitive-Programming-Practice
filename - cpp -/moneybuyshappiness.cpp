#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1974E

//this problem is kinda deceptive. On one side, they give a limit for the sum of h[i] <= 10^5, but on the other
//side, they don't limit n. This forces you to use iterative dp, with 
//dp[i][j] = maximum money given that we're on the ith month and our current happiness is j. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll x;
        cin >> n >> x;
        vector<ll> c(n), h(n);
        ll h_sum = 0;
        for(int i = 0; i < n; i++){
            cin >> c[i] >> h[i];
            h_sum += h[i];
        }
        vector<vector<ll>> dp(n + 1, vector<ll>(h_sum + 1, -1));
        dp[0][0] = 0;
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= h_sum; j++){
                if(dp[i][j] == -1){
                    continue;
                }
                ll c_money = dp[i][j];
                //pay
                if(c_money >= c[i]) {
                    dp[i + 1][j + h[i]] = max(dp[i + 1][j + h[i]], c_money - c[i] + x);
                }
                //don't pay
                dp[i + 1][j] = max(dp[i + 1][j], c_money + x);
            }
        }
        for(int i = 0; i <= h_sum; i++){
            if(dp[n][i] != -1){
                ans = max(ans, i);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
