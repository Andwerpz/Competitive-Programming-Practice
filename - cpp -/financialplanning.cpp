#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - financialplanning

//first, sort the investment options by increasing ratio of startup cost / daily profit, which is equal to
//the amount of days the investment requires to pay itself off. 

//then, try out buying all prefixes of the investment list. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll m;
    cin >> m;
    vector<pair<ll, ll>> a(n, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), [](pair<ll, ll>& a, pair<ll, ll>& b) -> bool {
        ll r_a = a.second / a.first;
        ll r_b = b.second / b.first;
        return r_a < r_b;
    });
    ll ans = 1e18;
    ll d_profit = 0;
    ll i_cost = m;
    for(int i = 0; i < n; i++){
        d_profit += a[i].first;
        i_cost += a[i].second;
        ans = min(ans, (i_cost - 1) / d_profit + 1);
    }
    cout << ans << "\n";
    
    return 0;
}
