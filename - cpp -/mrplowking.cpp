#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - plowking

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
ll arith_sum(ll start, ll nr_elem, ll inc) {
    ll ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    ll ans = n * (n - 1) / 2;
    m -= n - 1;
    for(ll i = 1; i <= n; i++){
        ll amt = min(m, i);
        m -= amt;
        ans += amt * (n - i - 2);
        // cout << "I : " << i << " " << m << " " << amt << "\n";
    }
    cout << ans << "\n";
    
    return 0;
}
