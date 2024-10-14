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

//Codeforces - 2020B

//the operation will only turn off any perfect squares, leaving every other bulb on. 
//therefore we can just binary search for the first n, as the number of perfect squares below n is floor(sqrt(n)).

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll k;
        cin >> k;
        ll low = 0;
        ll high = 2e18;
        ll ans = high;
        while(low <= high){
            ll mid = low + (high - low) / 2;
            ll amt = mid - ((ll) sqrt((ld) mid));
            if(amt >= k){
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}