#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1928D

//we can consider the two parts adding and reducing the strength seperately. 

//the factor reducing the strength is a linear function with respect to S, the number of squads. Since it's
//linear, it has constant slope. 

//the factor increasing strength is increasing, with monotonically decreasing slope, but always greater than
//or equal to 0. 

//if we take the sum, we'll get a function with monotonically decreasing slope, that can go below zero. In 
//other words, we have a bitonic function. Thus, we can ternary search for the optimal answer. 

//s = number of squads
ll calc_val(vector<ll>& c, ll b, ll x, ll s) {
    ll ans = (s - 1) * x * -1;
    for(int i = 0; i < c.size(); i++){
        ll cnt = c[i];
        ll each = cnt / s;
        ll rem = cnt % s;
        if(each == 0){
            ans += b * rem * (rem - 1) / 2;
            continue;
        }
        ans += b * s * (each * each * (s - 1)) / 2; //bulk vs bulk
        ans += b * rem * (1 * each * (s - 1));  //rem vs bulk
        ans += b * rem * (rem - 1) / 2; //rem vs rem
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, b, x;
        cin >> n >> b >> x;
        vector<ll> c(n);
        for(int i = 0; i < n; i++){
            cin >> c[i];
        }
        ll low = 1;
        ll high = 1e9;
        while(high - low > 10) {
            ll m0 = low + (high - low) / 3 * 1;
            ll m1 = low + (high - low) / 3 * 2;
            ll v0 = calc_val(c, b, x, m0);
            ll v1 = calc_val(c, b, x, m1);
            if(v0 >= v1) {
                high = m1;
            }
            else {
                low = m0;
            }
        }
        ll ans = -1e18;
        for(int i = low; i <= high; i++){
            ans = max(ans, calc_val(c, b, x, i));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
