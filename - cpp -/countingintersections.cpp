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

//Spring 2025 Columbia University Local Contest - C

//just count the intersections from all the lines outgoing from each vertex, then multiply it by the number of
//vertices. Observe that each intersection is getting counted exactly 4 times, so divide by 4 to get the final
//answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        ll ans = 0;
        for(ll i = 1; i < n - 2; i++) ans += i * (n - 2 - i);
        ans *= n;
        ans /= 4;
        cout << ans << "\n";
    }
    
    return 0;
}