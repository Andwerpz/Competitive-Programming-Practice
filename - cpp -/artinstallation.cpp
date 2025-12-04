#include <bits/stdc++.h>
using namespace std;

//2025 NAQ - A

//holy moly implementation issue D:

//just buy enough LED for red and blue, then all the leftovers go into green. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int r, g, b;
    cin >> r >> g >> b;
    int cr, cg, cb;
    cin >> cr >> cg >> cb;
    r = max(0, r - cr);
    g = max(0, g - cg);
    b = max(0, b - cb);
    int sr, sb;
    cin >> sr >> sb;
    int ans = 0;
    if(sr < r) {
        // cout << "FAIL1\n";
        cout << "-1\n";
        return 0;
    }
    assert(sr >= r);
    ans += r;
    sr -= r;
    r = 0;
    // cout << "SB B : " << sb << " " << b << "\n";
    if(sb < b) {
        // cout << "Fail2\n";
        cout << "-1\n";
        return 0;
    }
    assert(sb >= b);
    ans += b;
    sb -= b;
    b = 0;
    // cout << (sr + sb) << " " << g << endl;
    if((sr + sb) < g) {
        cout << "-1\n";
        return 0;
    }
    assert(sr + sb >= g);
    ans += g;
    cout << ans << "\n";

    return 0;
}