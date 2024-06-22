#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1976B

//for all a[i] where i < n, we just take the most direct path towards b[i]. If we ever have an intermediate value
//equal to b[n], we just copy it over. Otherwise, the cost for b[n] is just the minimum difference between it and 
//any a[i] or b[i], plus 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n), b(n + 1);
        ll e_cost = 1e9;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i <= n; i++){
            cin >> b[i];
        }
        for(int i = 0; i < n; i++){
            e_cost = min(e_cost, abs(a[i] - b[n]) + 1);
            e_cost = min(e_cost, abs(b[i] - b[n]) + 1);
            if(min(a[i], b[i]) <= b[n] && b[n] <= max(a[i], b[i])) {
                e_cost = min(e_cost, (ll) 1);
            }
            ans += abs(a[i] - b[i]);
        }
        ans += e_cost;
        cout << ans << "\n";
    }
    
    return 0;
}