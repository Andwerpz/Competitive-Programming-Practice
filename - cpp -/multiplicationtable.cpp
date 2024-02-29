#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 448D

//given some value x, we can test in O(n) time how many numbers in the table are strictly less than it. 
//then, we can binary search over x, and pick the maximum x where the number of values that are less than it
//is strictly less than k. 

bool is_valid(ll n, ll m, ll k, ll val) {
    ll cnt = 0;
    for(ll i = 1; i <= n; i++){
        ll nr_less = min(m, (val - 1) / i);
        cnt += nr_less;
    }
    return cnt < k;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k;
    cin >> n >> m >> k;
    ll low = 0;
    ll high = n * m;
    ll ans = low;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(is_valid(n, m, k, mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
