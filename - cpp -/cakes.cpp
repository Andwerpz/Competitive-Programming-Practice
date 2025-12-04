#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

//SWERC 2020 - E

signed main() {
    int n; cin >> n;
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ans = min(ans, y / x);
    }

    cout << ans << '\n';
}
