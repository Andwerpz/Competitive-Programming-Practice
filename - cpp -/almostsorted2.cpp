#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC132C

//we can do a 2d bitmask dp. 
//dp[i][j] is the number of ways to pick the values in p from [0, i) where j is the bitmask representing
//the 2 * d + 1 values around j, 0 if not used, and 1 if used. 

//of course, if a[i] != -1, then we can only pick a[i] for p[i]. 
//otherwise, we need to pick some value in the range [i - d, i + d]. We use the bitmask to determine
//what we can pick. 

//one thing to note is that we can't 'miss' any values, or in other words, we have to make sure to pick every 
//value, in order to make p a permutation. 

//complexity is n * 2^(d * 2 + 1)

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
                //cout << dp[i][j] << " ";
                int last_val = i - d;
                if(last_val > 0 && !used[last_val] && (j & 1) == 0) {
                    continue;
                }
                dp[i + 1][j >> 1] += dp[i][j];
                dp[i + 1][j >> 1] %= mod;
            }
            //cout << "\n";
            continue;
        }
        //cout << "I : " << i << "\n";
        for(int j = 0; j < dp[0].size(); j++){
            //cout << dp[i][j] << " ";
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
                // if(dp[i][bits] != 0){
                //     cout << i << " " << bits << " " << dp[i][bits] << " " << n_bits << " " << try_val << "\n";
                // }
                dp[i + 1][n_bits] += dp[i][bits];
                dp[i + 1][n_bits] %= mod;
            }
        }
        //cout << "\n";
    }
    ll ans = 0;
    for(int i = 0; i < dp[0].size(); i++){
        //cout << dp[n][i] << " ";
        ans += dp[n][i];
        ans %= mod;
    }
    //cout << "\n";
    cout << ans << "\n";
    
    return 0;
}
