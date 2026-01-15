#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - G

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

        int n, a, b; cin >> n >> a >> b;
        vector<pii> v(n);
        for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;

        long double ans = 1;
        for (int i = 0; i < n; i++) {
            ll l = max(v[i].first, a);
            ll r = min(v[i].second, b);
            ll overlap = max(r - l, (ll)0);

            ans *= (long double)overlap / (b - a);
        }

        cout << fixed << setprecision(9) << 1.0 - ans << '\n';


    return 0;
}