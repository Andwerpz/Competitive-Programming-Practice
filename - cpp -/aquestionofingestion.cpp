#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 07 A

//two state dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<ll> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(2, vector<ll>(100, 0)));
    for(int i = 0; i < n; i++){
        ll amt = m;
        ld mul = 1.00000000001;
        for(int j = 0; j < 100; j++){
            //haven't eaten previously
            if(j != 99){
                dp[i + 1][1][j + 1] = max(dp[i + 1][1][j + 1], dp[i][0][j] + min(a[i], amt));
            }
            dp[i + 1][0][0] = max(dp[i + 1][0][0], dp[i][0][j]);
            //have eaten previously
            if(j != 99){
                dp[i + 1][1][j + 1] = max(dp[i + 1][1][j + 1], dp[i][1][j] + min(a[i], amt));
            }
            if(j != 0){
               dp[i + 1][0][j - 1] = max(dp[i + 1][0][j - 1], dp[i][1][j]); 
            }
            mul *= 2.0 / 3.0;
            amt = (int) (amt * (2.0 / 3.0) + 0.000001);
        }
    }
    ll ans = 0;
    for(int i = 0; i < 100; i++){
        ans = max(ans, dp[n][0][i]);
        ans = max(ans, dp[n][1][i]);
    }
    cout << ans << "\n";
    
    return 0;
}
