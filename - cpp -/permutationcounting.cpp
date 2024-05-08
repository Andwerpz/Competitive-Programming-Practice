#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1967A

//

bool is_valid(vector<ll>& a, ll val, ll k) {
    for(int i = 0; i < a.size(); i++){
        k -= max(0ll, val - a[i]);
    }
    return k >= 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll low = a[0];
        ll high = 1e13;
        ll setval = low;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if(is_valid(a, mid, k)) {
                setval = max(setval, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        for(int i = 0; i < n; i++){
            k -= max(0ll, setval - a[i]);
            a[i] = max(a[i], setval);
        }
        for(int i = 0; i < n; i++){
            if(k != 0){
                a[i] ++;
                k --;
            }
        }
        sort(a.begin(), a.end());
        ll minv = a[0];
        ll ans = 1 + (minv - 1) * n;
        for(int i = 0; i < n; i++){
            if(a[i] != minv) {
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
