#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> r(n), c(n);
    for(int i = 0; i < n; i++){
        cin >> r[i] >> c[i];
    }
    sort(r.begin(), r.end());
    sort(c.begin(), c.end());
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += abs(r[i] - (i + 1)) + abs(c[i] - (i + 1));
    }
    cout << ans << "\n";
    
    return 0;
}
