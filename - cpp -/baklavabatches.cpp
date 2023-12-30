#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 C

//put all the entries of a into a bst, and for each entry of b, look for the closest entry of a above it and below it. 

//for entries below, we can always make them given that n >= 2. If n == 1, then we can't move baklavas around. 

//for entries above, we just have to check if we have enough baklavas to make up the difference. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    set<ll> orders;
    ll b_sum = 0;
    for(int i = 0; i < n; i++){
        orders.insert(a[i]);
        b_sum += b[i];
    }
    ll ans = 1e18;
    for(int i = 0; i < n; i++){
        if(*orders.begin() <= b[i]){
            ll order = *(--orders.lower_bound(b[i]));
            ll diff = abs(b[i] - order);
            if(n != 1){
                ans = min(ans, diff);
            }
        }
        if(*orders.rbegin() >= b[i]) {
            ll order = *(orders.lower_bound(b[i]));
            ll diff = abs(b[i] - order);
            ll rem_sum = b_sum - b[i];
            if(rem_sum >= diff) {
                ans = min(ans, diff);
            }
        }
    }
    if(ans == 1e18){
        cout << "-1\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}
