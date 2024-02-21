#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NCPC 2019 - G

//

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
ll arith_sum(ll start, ll nr_elem, ll inc) {
    ll ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

ll solve(ll n, ll m, ll k, ll g){
    if(g < 0){
        return -1;
    }
    //g is the amount of k-groups we're making
    ll ans = arith_sum(n, g, -k);
    n -= g * k;
    if(n < 0 || n > m * (k - 1)) {
        return -1;
    }
    ll size = n / m;
    ll nr_p1 = n % m;
    ll nr_p0 = m - nr_p1;
    ans += arith_sum(n, nr_p1, -(size + 1));
    n -= nr_p1 * (size + 1);
    ans += arith_sum(n, nr_p0, -size);
    n -= nr_p0 * size;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k;
    cin >> n >> m >> k;
    ll ans = 0;
    for(ll i = n / k - m; i <= n / k; i++){
        ans = max(ans, solve(n, m, k, i));
    }
    cout << ans << "\n";
    
    return 0;
}
