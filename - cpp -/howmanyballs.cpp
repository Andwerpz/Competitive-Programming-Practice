#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

//ICPC ECNA 2025 - G

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);


    
    auto solve = [&](int p, int q) -> pair<ll, ll> {
        for (ll r = 1; r <= (int)1e6; r++) {
            ll a = p;
            ll b = (r * 2 - 1) * p - 2 * r * q;
            ll c = (r * r - r) * p;
            ll d2 = b * b - c * a * 4;

            if (d2 < 0) continue;
            ll d = sqrt(d2);
            if (d * d != d2) continue;
            if ((-b + d) % (2 * a)) continue;
            ll g = (-b + d) / (2 * a);

            return {r, g};
        }
        return {-1, -1};
    };

    bool debug = false;
    ll p, q;
    if (debug) {
        for (int p = 1; p <= 1000; p++) {
            for (int q = p * 2 - 1; q <= 1000; q++) {
                auto [r, g] = solve(p, q);
                if (r >= 0 && g < 0) {
                    cout << p << " " << q << " " << r << " " << g << '\n';
                    exit(0);
                }
            }
        }
    } else {
        cin >> p >> q;
        auto [r, g] = solve(p, q);
        if (r >= 0) cout << r << " " << g << '\n';
        else cout << "impossible\n";
    }


    return 0;
}