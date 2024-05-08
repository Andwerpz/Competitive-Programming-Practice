#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - D

//sort the cupcakes in ascending order by (a * s[i] + b)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    ll a, b;
    cin >> a >> b;
    vector<ll> c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
        c[i] = c[i] * a + b;
    }
    sort(c.begin(), c.end());
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += c[i] * (i + 1);
    }
    cout << ans << "\n";
    
    return 0;
}
