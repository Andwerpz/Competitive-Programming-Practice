#include <bits/stdc++.h>
typedef long long ll;
// typedef __ll128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2020 - E

//we can directly simulate the problem using prefix sum range update technique. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, q; cin >> n >> q;

    vector<ll> slopes(n+2);

    while (q--) {
        char c; cin >> c;
        if (c == 'R') {
            ll x1, x2; cin >> x1 >> x2;
            if (x1 == x2) {
                slopes[x1-1]++;
                slopes[x2] -= 2;
                slopes[x2+1]++;
            } else {

                slopes[x1-1]++;
                slopes[x1]--;

                slopes[x2]--;
                slopes[x2+1]++;

            }
        } else if (c == 'D') {

            ll x1, x2; cin >> x1 >> x2;
            if (x1 == x2) {
                slopes[x1-1]--;
                slopes[x2] += 2;
                slopes[x2+1]--;
            } else {

                slopes[x1-1]--;
                slopes[x1]++;

                slopes[x2]++;
                slopes[x2+1]--;

            }

        } else if (c == 'H') {
            ll x1, x2; cin >> x1 >> x2;
            slopes[x1-1]++;
            slopes[x2+1]++;

            if ((x2 - x1 + 1) % 2 == 0) {
                // two tops
                ll total = (x2 - x1 + 1) / 2;
                ll mid = x1 + total - 1;
                slopes[mid]--;
                slopes[mid+1]--;
            } else {
                // one top
                ll mid = x1 + (x2 - x1) / 2;
                slopes[mid] -= 2;
            }

        } else {

            ll x1, x2; cin >> x1 >> x2;
            slopes[x1-1]--;
            slopes[x2+1]--;

            if ((x2 - x1 + 1) % 2 == 0) {
                // two tops
                ll total = (x2 - x1 + 1) / 2;
                ll mid = x1 + total - 1;
                slopes[mid]++;
                slopes[mid+1]++;
            } else {
                // one top
                ll mid = x1 + (x2 - x1) / 2;
                slopes[mid] += 2;
            }
        }
    }

    ll pos = slopes[0];
    ll slope = slopes[0];
    for (ll i = 1; i <= n; ++i) {
        cout << pos << endl;
        slope += slopes[i];
        pos += slope;
    }
    
    return 0;
}
