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

//Codeforces - 2086E

//First, observe that the z-value of any power of 2 is at most 4. This means that for any number x, the upper
//bound on the z-value is log_2(x) * 4, as we can just decompose it into its powers of 2 and then recompose each
//power of 2 independently using zebra numbers. 

//how can we compute the actual z-value for arbitrary numbers? Define z[i] as the ith zebra number. Observe that
//z[i + 1] = 4 * z[i] + 1. One way of computing the z-value of x is to start off with x 1s, which is z[0], 
//and then combine them, greedily combining the largest, until you can't combine anymore. This leads to a 
//base-5 like counting, the z-value is essentially the sum of digits of x in base 5 (ish). 

//We can then compute the number of such x in range [0, z[i]) where the z-score is equal to some k using some
//recursive dp. Since we know the upper bound on the z-value is relatively low, if we ever ask for k higher than
//200ish, we can just return 0. 

ll calc_zval(ll a) {
    vl b(32, 0);
    b[0] = a;
    while(true) {
        if(b[0] == 0) break;
        bool found = false;
        for(int i = b.size() - 1; i >= 0; i--){
            if(b[i] >= 4) {
                if(i == 0 && b[i] < 5) break;
                found = true;
                b[i] -= 4;
                b[i + 1] += 1;
                b[0] --;
            }
        }
        if(!found) break;
    }
    for(int i = 0; i < b.size(); i++) cout << b[i] << " ";
    cout << "\n";
    ll ans = 0;
    for(int i = 0; i < b.size(); i++) ans += b[i];
    return ans;
}

void cntup(ll lim) {
    vl b(20, 0);
    for(int i = 0; i <= lim; i++){
        for(int x : b) cout << x << " ";
        cout << ": " << i << "\n";
        b[0] ++;
        while(true) {
            if(b[0] == 0) break;
            bool found = false;
            for(int i = b.size() - 1; i >= 0; i--){
                if(b[i] >= 4) {
                    if(i == 0 && b[i] < 5) break;
                    found = true;
                    b[i] -= 4;
                    b[i + 1] += 1;
                    b[0] --;
                }
            }
            if(!found) break;
        }
    }
}

vl z(32);
vvl dp(32, vl(200, -1));    

//computes the amount of numbers in range [0, z[zind]) such that zebra value = k
ll calc_pfx(int zind, int k) {
    if(zind == 0) return k == 0? 1 : 0;
    if(k < 0) return 0;
    if(dp[zind][k] != -1) return dp[zind][k];
    ll ans = 0;
    ans += calc_pfx(zind - 1, k - 0);
    ans += calc_pfx(zind - 1, k - 1);
    ans += calc_pfx(zind - 1, k - 2);
    ans += calc_pfx(zind - 1, k - 3);
    if(k == 4) ans ++;
    dp[zind][k] = ans;
    // cout << "DP : " << zind << " " << k << " " << ans << "\n";
    return ans;
}

//computes the amount of numbers in range [0, r) such that the zebra value = k. 
ll calc_amt(ll r, ll k) {
    if(k >= dp[0].size()) return 0;
    int i = 0;
    while(z[i] < r) i++;
    ll ans = 0;
    while(r != 0) {
        while(z[i] > r) i --;
        while(r >= z[i]) {
            // cout << "CALC PFX : " << i << " " << k << "\n";
            ans += calc_pfx(i, k);
            k --;
            r -= z[i];
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    //precalc all zebra numbers
    z[0] = 1;
    for(int i = 1; i < z.size(); i++){
        z[i] = z[i - 1] * 4 + 1;
    }
    // for(int i = 0; i < z.size(); i++) cout << z[i] << "\n";
    // cout << ((ll) 1e18) << "\n";

    int t;
    cin >> t;
    while(t--){
        ll l, r, k;
        cin >> l >> r >> k;
        r ++;
        ll ans = calc_amt(r, k) - calc_amt(l, k);
        cout << ans << "\n";
    }

    // calc_zval(19);
    // int cnt = 0;
    // for(int i = 1; i <= 100; i++){
    //     // calc_zval(i);
    //     // cout << "I : " << i << " " << calc_zval(i) << "\n";
    //     // cnt += calc_zval(i) == 3;
    // }
    // cout << "CNT : " << cnt << "\n";
    // cntup(100);
    
    return 0;
}