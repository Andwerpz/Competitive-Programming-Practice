#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef long double ld;

//2025 NAQ - I

//just sort all the people in descending order, and try all prefixes. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vl s(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());
    ll sum = 0;
    ld ans = 0;
    for(int i = 0; i < n; i++) {
        sum += s[i];
        ans = max(ans, (ld) (sum + a[i]) / (ld) (i + 1));
    }
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}