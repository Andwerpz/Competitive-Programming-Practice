#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

//ICPC ECNA 2025 - F

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n; cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    n--;
    ll l = 1, r = 1e7;
    while (l < r) {
        ll mid = (l + r + 1) / 2;
        if (mid * (mid - 1) / 2 <= n) l = mid;
        else r = mid - 1;
    }

    cout << l;
    ll k = n - l * (l - 1) / 2;
    if (k) cout << " " << k / gcd(k, l) << "/" << l / gcd(k, l);
    cout << '\n';

    return 0;
}