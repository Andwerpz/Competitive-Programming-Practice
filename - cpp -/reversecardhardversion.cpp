#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1967B2

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        ll ans = 0;
        for(ll x = 1; x <= max(n, m); x++){
            cout << "X : " << x << "\n";
            for(ll g = x + 1;; g++){
                cout << "G : " << g << "\n";
                ll num = g - x;
                ll denom = x;
                ll fg = gcd(num, denom);
                num /= fg;
                denom /= fg;
                ll a = num * g;
                ll b = denom * g;
                if(a > n || b > m){
                    break;
                }
                cout << "VALID : " << a << " " << b << "\n";
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
