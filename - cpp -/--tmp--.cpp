#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] != -1) {
            a[i] --;    
        }
    }
    vector<int> used(n, false);
    for(int i = 0; i < n; i++){
        if(a[i] != -1){
            used[a[i]] = true;
        }
    }
    vector<vector<ll>> dp(n + 1, vector<ll>((1 << (d * 2 + 1)), 0));
    dp[0][0] = 1;
    ll mod = 998244353;
    for(int i = 0; i < n; i++){
        if(a[i] != -1){
            if(abs(a[i] - i) > d) {
                continue;
            }
            for(int j = 0; j < dp[0].size(); j++){
                int last_val = i - d;
                if(last_val > 0 && !used[last_val] && (j & 1) == 0) {
                    continue;
                }
                dp[i + 1][j >> 1] += dp[i][j];
                dp[i + 1][j >> 1] %= mod;
            }
            continue;
        }
        for(int j = 0; j < dp[0].size(); j++){
            int bits = j;
            for(int k = 0; k < 2 * d + 1; k++){
                if(bits & (1 << k)) {
                    continue;
                }
                int try_val = i - d + k;
                if(try_val < 0 || try_val >= n || used[try_val]) {
                    continue;
                }
                int last_val = i - d;
                if(try_val != last_val && last_val > 0 && !used[last_val] && (j & 1) == 0) {
                    continue;
                }
                int n_bits = bits >> 1;
                if(k > 0) {
                    n_bits |= (1 << (k - 1));
                }
                dp[i + 1][n_bits] += dp[i][bits];
                dp[i + 1][n_bits] %= mod;
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < dp[0].size(); i++){
        ans += dp[n][i];
        ans %= mod;
    }
    cout << ans << "\n";
    
    return 0;
}
