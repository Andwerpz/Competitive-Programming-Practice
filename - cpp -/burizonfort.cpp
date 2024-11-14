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

//CTU Open 2021 - D

void solve() {
    ll n; cin >> n;
    vector<ll> facs;
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            facs.push_back(i);
            if (n / i != i)
                facs.push_back(n / i);
        }
    }

    sort(facs.begin(), facs.end());

    ll cnt = 0;
    bool works = true;
    for (auto f : facs) {
        if (cnt >= n - 1)
            break;
        if (f > cnt + 1)
            works = false;
        cnt += f;
        // cerr << "cnt : " << cnt << " f : " << f << endl;
    }

    if (works)
        cout << "Yes\n";
    else
        cout << "No\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int tc; cin >> tc;
    while (tc--) {
        solve();
    }   
    
    return 0;
}