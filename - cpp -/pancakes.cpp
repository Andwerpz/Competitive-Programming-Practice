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

// UTPC 10-1-25 Div1 - E

//how can we tell if our pekka will win? 
//if (h2 + a1 - 1) / a1 < (h1 + a2 - 1) / a2, then our pekka will win 

//notice that increasing attack lowers the left side and increasing health raises the right side.
//recall that when floor dividing, there are only around sqrt(N) breakpoints where the quotient decreases
//so we can just look through all of those quotients and take the best one. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll tmp = 0;
    ll a1, h1, a2, h2;
    cin >> a1 >> h1 >> a2 >> h2;
    ll ans = 1e18;
    ll a = a1;
    while(true) {   
        ll l = (h2 + a - 1) / a;
        ll r = (h1 + a2 - 1) / a2;
        ans = min(ans, a - a1 + max(0ll, (l * a2 + 1) - h1));
        if((h2 + a - 1) / a == 1) break;
        ll low = a + 1, high = 1e9;
        ll na = high;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if((h2 + mid - 1) / mid < l) {
                na = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }  
        a = na;
    }
    cout << ans << "\n";

    return 0;
}