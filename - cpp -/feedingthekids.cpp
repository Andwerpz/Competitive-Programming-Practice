#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - D

//binary search across how many slices you need to cut each pizza into. 

bool is_valid(ll k, vector<ll>& a, ll val) {
    ll cur = 0;
    for(int i = 0; i < a.size(); i++){
        if(a[i] > val) {
            return false;
        }
        if(cur < a[i]) {
            if(k == 0){
                return false;
            }
            k --;
            cur = val;
        }
        cur -= a[i];
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll low = 1;
    ll high = 1e18;
    ll ans = high;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(is_valid(k, a, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
