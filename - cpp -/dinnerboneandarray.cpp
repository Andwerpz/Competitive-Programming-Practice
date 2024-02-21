#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 01-26-24 Div. 2 - G

//just try all subsets. 

//strict subset means that you can't just take the entire thing as the subset. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll mx = -1e18;
        ll mn = 1e18;
        for(int bits = 0; bits < (1 << n); bits++){
            ll nr_elem = 0;
            ll cur = 0;
            for(int i = 0; i < n; i++){
                if((bits >> i) & 1) {
                    nr_elem ++;
                    cur += a[i] * a[i] * a[i];
                }
            }
            if(nr_elem == n){
                continue;
            }
            cur *= nr_elem * (nr_elem % 2 == 1? -1 : 1);
            mx = max(mx, cur);
            mn = min(mn, cur);
        }
        cout << mn << " " << mx << "\n";
    }
    
    return 0;
}
