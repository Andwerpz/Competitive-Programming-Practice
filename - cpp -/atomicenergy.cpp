#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - A

//i don't know why this one works. 

//first, compute the correct answer for all values from 1 to 1e6
//then, given k, we will try just splitting 1 amount of neutrons until k <= 1e6. Try all possible
//amounts from 1 to n, and take the minimum answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for(int i = 0; i < n; i++){
        cin >> a[i + 1];
    }
    vector<ll> dp(1000000 + 1);
    for(int i = 0; i <= n; i++){
        dp[i] = a[i];
    }
    for(int i = n + 1; i < dp.size(); i++){
        dp[i] = 1e18;
        for(int j = i-1; j >= i - n; j--){
            dp[i] = min(dp[i], dp[j] + dp[i - j]);
        }
    }
    for(int i = 0; i < q; i++){
        ll k_orig;
        cin >> k_orig;
        ll ans = 1e18;
        for(ll j = 1; j <= n; j++){
            ll k = k_orig;
            ll cur_ans = 0;
            if(k > 1000000){
                ll diff = k - 900000;
                ll mult = diff / j;
                k -= j * mult;
                cur_ans += mult * a[j];
            }
            cur_ans += dp[k];
            ans = min(ans, cur_ans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
