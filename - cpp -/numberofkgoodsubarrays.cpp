#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1982E

//for some segment [0, n), let's say that it's characteristic tuple is of the form {l, r, s}, where
//l is the maximum prefix of good values, r is the maximum suffix of good values, and s is the number
//of subarrays of good values that don't contain any prefix or suffix values. 

//for some p, p >= 0, notice that the answer to [0, 2^p) for some k is the same as the answer to [2^p, 2^(p + 1))
//with k - 1. yada yada, use a divide and conquer approach, we only have to keep track of current value
//of k and number of bits, leading to around log(n)^2 states. 

ll mod = 1e9 + 7;  

tuple<ll, ll, ll> combine(tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {
    ll l0 = get<0>(a), r0 = get<1>(a), s0 = get<2>(a);
    ll l1 = get<0>(b), r1 = get<1>(b), s1 = get<2>(b);
    ll l = l0;
    ll r = r1;
    ll s = s0 + s1;
    if(r0 == -1 && r1 == -1){
        l = l0 + l1;
        r = -1;
    }
    else if(r0 == -1){
        l = l0 + l1;
    }
    else if(r1 == -1){
        r = r0 + l1;
    }
    else {
        ll sz = (r0 + l1) % mod;
        s += sz * (sz + 1) / 2;
        s %= mod;
    }
    l %= mod;
    if(r != -1){
        r %= mod;
    }
    return {l, r, s};
}

tuple<ll, ll, ll> _solve(int bit, int k, vector<vector<tuple<ll, ll, ll>>>& dp) {
    if(k < 0){
        return {0, 0, 0};
    }
    if(bit == 0){
        return {1, -1, 0};
    }
    if(get<0>(dp[bit][k]) != -1){
        return dp[bit][k];
    }
    dp[bit][k] = combine(_solve(bit - 1, k, dp), _solve(bit - 1, k - 1, dp));
    return dp[bit][k];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<vector<tuple<ll, ll, ll>>> dp(61, vector<tuple<ll, ll, ll>>(61, {-1, -1, -1}));
        tuple<ll, ll, ll> sum = {0, -1, 0};
        while(n != 0){
            int bit = 63 - __builtin_clzll(n);
            // cout << "SOLVE : " << bit << " " << k << "\n";
            sum = combine(sum, _solve(bit, k, dp));
            n -= (1ll << bit);
            k --;
            // cout << "SUM : " << get<0>(sum) << " " << get<1>(sum) << " " << get<2>(sum) << "\n";
        }
        ll l = get<0>(sum);
        ll r = get<1>(sum);
        ll ans = get<2>(sum);
        l %= mod;
        ans += l * (l + 1) / 2;
        if(r != -1){
            r %= mod;
            ans += r * (r + 1) / 2;
        }
        ans %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}