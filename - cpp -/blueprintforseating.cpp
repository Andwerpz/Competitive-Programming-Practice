#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC 2023–2024 NERC B

//first, we want to compute the minimum inconvenience. 
//consider each aisle as having two 'sides' which consist of the seats that are closest to it. 
//in this way, the window seats are identical to the center group seats. 
//then, when we add a seat to a side of an aisle, the inconvenience will increase by exactly the amount of 
//seats that were originally there. 
//thus, we want to greedily add seats to aisles that have the minimum amount of seats. Using this method, we can
//pretty easily compute the minimum inconvenience. 

//now, different configurations with minimum inconvenience happen when n % (k * 2) != 0; we can't evenly distribute
//seats among the aisle groups. Thus, we have to count the number of ways to distribute the remaining seats among
//the aisle groups. 

//the issue is that we can't just do k * 2 choose r, where r is the number of remaining seats. This is because in 
//the middle sections, placing a seat on either group is indistinguishable. 

//'|' = aisle, 'O' = seat
//initial state: each group has 1 seat. 
// O|O O|O

//adding a seat to the 2nd group is indistinguishable to adding a seat to the third group.
// O|OO O|O vs. O|O OO|O

//so instead, we will first fix the amount of seats that get assigned to the window groups, and merge the middle
//groups. For each middle group, we can add 0, 1, or 2 extra seats. We can fix the amount of groups that get 2 extra
//seats, and from there the number of groups with 1 and 0 extra seats are fixed as well. Then, the number of sitations
//where 'a' groups get 2, 'b' groups get 1, and 'c' groups get 0 is nck(k - 1, a) * nck(k - 1 - a, b). 
//note that k - 1 is the total amount of middle groups. 

//in the case where n < 2 * k, we will not be able to add a seat to every aisle group, then we have a slightly 
//different but simpler way to compute the number of combinations. (left as an exercise to the reader)

const ll MOD = 998244353;

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

//TODO replace with template that supports all modular operations
ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b) {
    return binexp(b,MOD-2) * a % MOD;
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

ll compute(ll num_middles, ll spareseats) {
    ll ans = 0;
    for(ll num_twos = 0; num_twos * 2 <= spareseats; num_twos++) {
        assert(num_twos <= num_middles);
        ll num_ones = spareseats - num_twos * 2;
        if(num_twos + num_ones > num_middles) {
            continue;
        }

        ll num_zeroes = num_middles - num_ones - num_twos;
        ans += choose(num_middles, num_twos) * choose(num_middles - num_twos, num_ones);
        ans %= MOD;
    }
    return ans;
}

void solve() {
    
    ll n, k; cin >> n >> k;

    ll greedy_fill = n / (k * 2);
    ll remainder = n - greedy_fill * k * 2;

    ll mincost = greedy_fill * (greedy_fill - 1) * k + remainder * (greedy_fill);

    // cout << "greedy fill : " << greedy_fill << " remainder : " << remainder << '\n';

    cout << mincost << ' ';
    if(n < k * 2) {
        //edge case
        ll remainder = n - (k + 1);
        ll num_middles = k - 1;
        ll ans = choose(num_middles, remainder);
        cout << ans << '\n';
    } else {
        ll ans = 0;
        ans += compute(k - 1, remainder);
        if(remainder > 0) {
            ans += compute(k - 1, remainder - 1) * 2;
        }
        if(remainder > 1) {
            ans += compute(k - 1, remainder - 2);
        }
        cout << ans % MOD << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    factorial();
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}