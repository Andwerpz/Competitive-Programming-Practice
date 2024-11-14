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

//CTU Open 2021 - F

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int tc; cin >> tc;
    while (tc--) {
        ll yp, lp, ys, ls;
        cin >> yp >> lp >> ys >> ls;

        ll y_time = yp * ys;

        ll l_time = yp * ls;
        l_time += abs(yp - lp) * ls;

        ll l2_time = abs(yp - lp) * ys + lp * ls;

        cout << min({y_time, l_time, l2_time}) << endl;
    }
    
    return 0;
}