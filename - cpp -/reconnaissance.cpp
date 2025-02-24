#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//2014 NAIPC - H

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    // while (n) {

        vector<pair<double, double>> cars(n);
        for (auto& p : cars)
            cin >> p.first >> p.second;
        

        auto check = [&](double t) -> double {
            double mn = 1e9, mx = -1e9;
            for (auto p : cars) {
                double coord = p.first + p.second * t;
                mn = min(mn, coord);
                mx = max(mx, coord);
            }
            // cerr << "MX : " << mx << " MN : " << mn << endl;
            return mx - mn;
        };
        
        double lo = 0, hi = 1e6;
        while (hi - lo > 1e-4) {
            // cerr << "HI : " << hi << " LO : " << lo << endl;
            double f_third = lo + (hi - lo) / 3;
            double s_third = hi - (hi - lo) / 3;
            double f_val = check(f_third);
            double s_val = check(s_third);

            if (f_val <= s_val) {
                hi = s_third;
            } else
                lo = f_third;
        }

        double ans = check(lo);
        cout << setprecision(5) << fixed;
        cout << ans << "\n";
        // check(100);
    // }
    
    return 0;
}