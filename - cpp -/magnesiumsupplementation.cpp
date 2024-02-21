#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - H

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k, p; cin >> n >> k >> p;
    vector<ll> ans;
    for (ll i = 1; (i * i <= n) && (i <= k); ++i) {
        if ((n % i) != 0) continue;
        // cerr << "i : " << i << endl;
        ll div = n / i;
        if (div <= p) {
            ans.push_back(i);
        }
        if (div <= k) {
            if (i <= p) {
                ans.push_back(div);
            }
        }
    }

    sort(begin(ans), end(ans));
    ans.erase(unique(begin(ans), end(ans)), end(ans));

    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x << endl;
    }
    
    return 0;
}
