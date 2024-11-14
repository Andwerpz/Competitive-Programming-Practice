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

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

// - slow version, use when big number 
vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.push_back(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.push_back(val);
    }
    return factors;
}

void find_divisors_helper(vector<ll>& p, vector<ll>& c, ll ind, ll val, vector<ll>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    find_divisors_helper(p, c, ind + 1, val, ans);
    for(ll i = 0; i < c[ind]; i++){
        val *= p[ind];
        find_divisors_helper(p, c, ind + 1, val, ans);
    }
}

//includes 1 as a divisor
vector<ll> find_divisors(ll val) {
    vector<ll> factors = find_prime_factors(val);
    map<ll, ll> m;
    vector<ll> p(0);
    vector<ll> c(0);
    for(ll i = 0; i < factors.size(); i++){
        ll next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        ll ind = m[next];
        c[ind] ++;
    }
    vector<ll> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
ll arith_sum(ll start, ll nr_elem, ll inc) {
    ll ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

//strat is to increase some amount of times, then attack. 
ll calc_cost(ll x, ll y, ll z, ll k, ll nr_inc) {
    ll ans = 0;
    ll nrg = (nr_inc + k - 1) / k;  //so, nrg - 1 attacks
    ans += x * nr_inc + y * (nrg - 1);
    z -= arith_sum(k, nrg - 1, k);
    z = max(z, 0ll);
    ll atk_dmg = nr_inc;
    ll nra = (z + atk_dmg - 1) / atk_dmg;
    ans += y * nra;
    // cout << "NRG : " << nrg << "\n";
    // cout << "ATK WHILE INC : " << arith_sum(k, nrg - 1, k) << "\n";
    return ans;
}

bool does_work(ll x, ll y, ll z, ll k, ll nr_inc, ll nr_atk){
    ll nrg = (nr_inc + k - 1) / k;  //nrg - 1 attacks
    ll nra = min(nrg - 1, nr_atk);
    z -= arith_sum(k, nra, k);
    nr_atk -= nra;
    ll atk_dmg = nr_inc;
    z -= nr_atk * atk_dmg;
    return z <= 0;
}

ll find_min_inc(ll x, ll y, ll z, ll k, ll nr_atk) {
    if(!does_work(x, y, z, k, z, nr_atk)) {
        return -1;
    }
    ll low = 1;
    ll high = z;
    ll ans = high;
    while(low <= high){
        ll mid = low + (high - low) / 2;
        if(does_work(x, y, z, k, mid, nr_atk)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return ans;
}

ll do_search(ll x, ll y, ll z, ll k, ll low, ll high){
    low = max(1ll, low);
    while(high - low > 100){
        ll m0 = low + ((high - low) / 3) * 1;
        ll m1 = low + ((high - low) / 3) * 2;
        ll v0 = calc_cost(x, y, z, k, m0);
        ll v1 = calc_cost(x, y, z, k, m1);
        if(v0 < v1) {
            high = m1;
        }
        else {
            low = m0;
        }
    }
    ll ans = 1e18;
    for(int i = low; i <= high; i++){
        ans = min(ans, calc_cost(x, y, z, k, i));
    }
    return ans;
}

ll ceil_div(ll a, ll b){
    return (a + b - 1) / b;
}

vector<ll> find_ceil_brk(ll a) {
    vector<ll> ans(0);
    for(int i = 1; i * i <= a; i++){
        ans.push_back(i);
        ans.push_back(ceil_div(a, i));
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6);
    int t;
    cin >> t;
    while(t--){
        ll x, y, z, k;
        cin >> x >> y >> z >> k;
        ll ans = 1e18;

        //find smallest attack amount that works
        ll nr_atk;
        {
            ll low = 1;
            ll high = z;
            nr_atk = z;
            while(low <= high){
                ll mid = low + (high - low) / 2;
                if(find_min_inc(x, y, z, k, mid) != -1){
                    nr_atk = mid;
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
        }
        //ternary search over the number of attacks
        ll low = nr_atk;
        ll high = z;
        while(high - low > 10){
            ll m0 = low + ((high - low) / 3) * 1;
            ll m1 = low + ((high - low) / 3) * 2;
            ll i0 = find_min_inc(x, y, z, k, m0);
            ll i1 = find_min_inc(x, y, z, k, m1);
            ll v0 = x * i0 + y * m0;
            ll v1 = x * i1 + y * m1;
            if(v0 < v1){
                high = m1;
            }
            else {
                low = m0;
            }
        }
        for(ll i = max(1ll, low - 10000); i <= high + 10000; i++){
            ll inc = find_min_inc(x, y, z, k, i);
            if(inc == -1){
                continue;
            }
            ans = min(ans, x * inc + y * i);
        }

        // for(ll i = 1; i < 20; i++){
        //     ll inc = find_min_inc(x, y, z, k, i);
        //     cout << "MIN INC : " << inc << " " << x * inc + y * i << "\n";
        // }

        // int nr_iter = 0;
        // while(nr_iter < 100){
        //     nr_iter ++;
        //     ll min_inc = find_min_inc(x, y, z, k, nr_atk);
        //     nr_atk ++;
        //     if(min_inc == -1){
        //         continue;
        //     }
        //     if(min_inc < 1e6) {
        //         break;
        //     }
        //     ans = min(ans, calc_cost(x, y, z, k, min_inc));
        // }

        // vector<ll> cb = find_ceil_brk(z);
        // for(int i = 0; i < cb.size(); i++){
        //     ll l = max(1ll, cb[i] - 20);
        //     ll r = cb[i] + 20;
        //     for(int j = l; j <= r; j++){
        //         ans = min(ans, calc_cost(x, y, z, k, j));
        //     }
        //     cout << "SEARCH : " << cb[i] << "\n";
        // }
        // for(int i = 0; i < div.size(); i++){
        //     ans = min(ans, do_search(x, y, z, k, div[i] - 10000, div[i] + 100));
        // }
        // for(ll i = 1; i < (ll) sqrt(z) + 100; i++){
        //     ans = min(ans, calc_cost(x, y, z, k, i));
        // }
        // for(ll i = 1; i < 1e6 + 100; i++){
        //     ans = min(ans, calc_cost(x, y, z, k, i));
        // }
        cout << ans << "\n";

        // ll low = 1;
        // ll high = 2e8;
        // while(high - low > 100){
        //     ll m0 = low + ((high - low) / 3) * 1;
        //     ll m1 = low + ((high - low) / 3) * 2;
        //     ll v0 = calc_cost(x, y, z, k, m0);
        //     ll v1 = calc_cost(x, y, z, k, m1);
        //     if(v0 < v1) {
        //         high = m1;
        //     }
        //     else {
        //         low = m0;
        //     }
        // }
        // // cout << "LH : " << low << " " << high << "\n";
        // ll ans = 1e18;
        // for(ll i = 1; i < (ll) sqrt(z) + 100; i++){
        //     ans = min(ans, calc_cost(x, y, z, k, i));
        // }
        // for(ll i = max(1ll, low - 100000); i < high + 100000; i++){
        //     ans = min(ans, calc_cost(x, y, z, k, i));
        // }
        // // for(ll i = low; i <= high; i++){
        // //     ll cans = calc_cost(x, y, z, k, i * k);
        // //     cout << "CALC : " << i << " " << cans << "\n";
        // //     ans = min(ans, cans);
        // // }
        // cout << ans << "\n";
    }
    
    return 0;
}