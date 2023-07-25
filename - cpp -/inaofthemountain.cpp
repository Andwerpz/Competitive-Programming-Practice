#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] %= k;
        }
        int x = 80;
        vector<vector<ll>> dp(n, vector<ll>(x, 1e18));
        for(int i = 0; i < x; i++){
            dp[0][i] = a[0] + k * (ll) i;   
        }
        for(int i = 0; i < n - 1; i++){
            for(int y = 0; y < x; y++){
                ll cur = a[i] + k * (ll) y;
                for(int z = 0; z < x; z++){
                    ll next = a[i + 1] + k * (ll) z;
                    dp[i + 1][z] = min(dp[i + 1][z], dp[i][y] + max(next - cur, 0ll));
                }
            }

            // for(int j = 0; j < x; j++){
            //     cout << dp[i][j] << " ";
            // }
            // cout << "\n";
        }
        ll ans = 1e18;
        for(int i = 0; i < x; i++){
            ans = min(ans, dp[n - 1][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
