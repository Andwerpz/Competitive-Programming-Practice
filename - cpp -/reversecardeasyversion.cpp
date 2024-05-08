#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1967B1

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        ll ans = 0;
        for(ll g = 1; g <= m; g++){
            for(ll a = g == 1? 1 : g * (g - 1); a <= n; a += g * g){
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
