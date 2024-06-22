#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1981B

//given some n, we can ask whether it'll have the ith bit at time m. As bits 'spread' one index per timestep, it's sufficient
//to compute the nearest numbers above and below n that have the ith bit initially, and see if the distance is less
//than or equal to m. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        ll ans = n;
        for(ll i = 0; i < 31; i++){
            if(n & ((ll) 1 << i)) {
                continue;
            }
            ll mask = ((ll) 1 << (i + 1)) - 1;
            ll x = n & mask;
            if((m >= x + 1 && x < n) || m >= ((ll) 1 << i) - x) {
                ans |= ((ll) 1 << i);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}