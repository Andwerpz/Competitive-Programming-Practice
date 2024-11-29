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

//CSES - 2194

//sweepline

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    ll ans = 9e18;
    set<pll> s; //{y, x}
    int lptr = 0;
    for(int i = 0; i < n; i++){
        while(lptr != i && (a[i].first - a[lptr].first) * (a[i].first - a[lptr].first) > ans) {
            s.erase({a[lptr].second, a[lptr].first});
            lptr ++;
        }
        auto ptr = s.lower_bound({(ll) (a[i].second - sqrt(ans) - 1), 0});
        while(ptr != s.end() && ptr->first - a[i].second <= sqrt(ans)) {
            ll dx = ptr->second - a[i].first;
            ll dy = ptr->first - a[i].second;
            ll cdist = dx * dx + dy * dy;
            if(cdist < ans) {
                ans = cdist;
            }
            ptr ++;
        }
        s.insert({a[i].second, a[i].first});
    }
    cout << ans << "\n";
    
    return 0;
}