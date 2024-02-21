#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - G

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int n, lph; cin >> n >> lph;

    lph *= 5;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(begin(a), end(a));

    int cnt = 0;
    int ans = 0;
    while (cnt < lph && ans < n) {
        cnt += a[ans];
        if (cnt <= lph)
            ans++;
    }

    cout << ans << endl;
        
    return 0;
}
