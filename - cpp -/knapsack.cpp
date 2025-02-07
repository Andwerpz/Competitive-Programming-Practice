#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1132E

//let s be the sum of all elements. If s <= w, then the answer is simply s, otherwise s > w. 

//If w is close to 0, lets say w < 1000, then we can brute force everything in range [0, 1000). 
//Similarly, if s - w < 1000, then we can use the same dp table we used for [0, 1000)

//Otherwise, w is somewhere in the middle. If we computed the dp table there, then one will notice that 
//the values are periodic there. We can just find the largest period in our computed table, and then 
//extrapolate the value at the position of w. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll w;
    cin >> w;
    vl f(9, 0);
    for(int i = 1; i <= 8; i++) cin >> f[i];
    ll sum = 0;
    for(int i = 1; i <= 8; i++) sum += i * f[i];
    if(sum <= w) {
        cout << sum << "\n";
        return 0;
    }
    vb dp(1000, false);
    dp[0] = true;
    for(int i = 1; i <= 8; i++){
        for(int j = dp.size() - 1; j >= 0; j--){
            if(!dp[j]) continue;
            for(int k = 1; k <= f[i]; k++){
                if(j + i * k >= dp.size()) break;
                dp[j + i * k] = true;
            }
        }
    }
    if(w < 1000) {
        ll ans = 0;
        for(int i = w; i >= 0; i--) if(dp[i]) {ans = i; break;}
        cout << ans << "\n";
        return 0;
    }
    if(sum - w < 1000){
        ll ans = 0;
        for(int i = sum - w; i < dp.size(); i++) if(dp[i]) {ans = sum - i; break;}
        cout << ans << "\n";
        return 0;
    }
    ll p = -1;
    for(int i = 500; i >= 1; i--){
        bool is_valid = true;
        for(int j = 0; j < i; j++){
            if(dp[dp.size() - i * 2 + j] != dp[dp.size() - i + j]) is_valid = false;
        }
        if(is_valid) {p = i; break;};
    }
    ll diff = w - 999;
    ll mult = (diff + p - 1) / p;
    ll ans = mult * p;
    w -= mult * p;
    for(int i = w; i >= 0; i--) if(dp[i]) {
        ans += i; break;
    }
    cout << ans << "\n";

    return 0;
}