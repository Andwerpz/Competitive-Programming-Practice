#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld r, c;
    cin >> r >> c;
    c = r - c;
    cout << fixed << setprecision(10) << (c * c * acos(-1)) / (r * r * acos(-1)) * 100 << "\n";
    
    return 0;
}
