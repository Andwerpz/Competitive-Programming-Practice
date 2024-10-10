#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - tractor

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll a, b;
        cin >> a >> b;
        ll ans = 1;
        ll pow = 1;
        while(true) {
            pow *= 2;
            ll c_pow = pow - 1;
            ll min_v = max(0ll, c_pow - a);
            ll min_h = max(0ll, c_pow - b);
            ll inc = 2 * pow - min_v - min_h;
            // cout << pow << " " << min_v << " " << min_h << "\n";
            if(min_v > b || min_h > a){
                break;
            }
            ans += pow - min_v - min_h;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
