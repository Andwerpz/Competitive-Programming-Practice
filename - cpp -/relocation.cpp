#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - K

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    while (q--) {
        int typ; cin >> typ;
        if (typ == 1) {
            int c, x; cin >> c >> x;
            a[c] = x;
        } else {
            int x, y; cin >> x >> y;
            cout << abs(a[x] - a[y]) << endl;
        }
    }
    
    return 0;
}
