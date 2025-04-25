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

//Codeforces - 1499D

//we're given c * lcm(a, b) - d * gcd(a, b) = x. Observe that lcm(a, b) is a multiple of gcd(a, b), therefore x must also be a
//multiple of gcd(a, b). So gcd(a, b) must be a divisor of x. 

//so let G = gcd(a, b), L = lcm(a, b), and G | x. Then, L = (x + d * G) / c. If (x + d * G) % c != 0, then this G is bad as L 
//must be an integer. Next, G | L must be true. If all these are satisfied, then we need to find the number of pairs (a, b) 
//such that G = gcd(a, b), L = lcm(a, b). If we take the prime factorization of a and b, gcd(a, b) takes the min out of the powers
//and lcm(a, b) takes the max. So the number of (a, b) is 2^c, where c is the amount of unique prime factors in L / G. 

//for all numbers from 1 to 2 * 10^7, we can precompute the primes and the number of unique prime factors in O(n * log(log(n))). 
//this solution is barely fast enough at around 1800 / 2000 ms. 

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
// vector<ll> find_prime_factors(ll val) {
//     vector<ll> factors(0);
//     for(int i = 0; i < pr.size(); i++){
//         while(val % pr[i] == 0){
//             factors.push_back(pr[i]);
//             val /= pr[i];
//         }
//     }
//     if(val != 1){
//         factors.push_back(val);
//     }
//     return factors;
// }

vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
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

void findp(ll l, ll g) {
    for(ll a = 1; a <= l; a++){
        for(ll b = 1; b <= l; b++){
            if(gcd(a, b) != g || lcm(a, b) != l) continue;
            cout << "FOUNDP : " << a << " " << b << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const ll N = 2e7 + 100;
    prime_sieve(2e7 + 100);
    vl ufcnt(N + 1, 0);
    for(ll& p : pr) {
        for(int i = p; i <= N; i += p) ufcnt[i] ++;
    }
    int t;
    cin >> t;
    while(t--){
        ll c, d, x;
        cin >> c >> d >> x;
        //gcd(a, b) must be a divisor of x
        int ans = 0;
        vl div = find_divisors(x);
        for(int i = 0; i < div.size(); i++){
            ll g = div[i];
            //c * lcm(a, b) - d * g = x
            //lcm(a, b) = (x + d * g) / c
            if((x + d * g) % c != 0) continue;
            ll l = (x + d * g) / c;
            //does there exist a pair of numbers such that gcd(a, b) = g, lcm(a, b) = l?
            if(l % g != 0) continue;    
            //l is a multiple of g
            //how many pairs (a, b) are there?
            ans += (1 << ufcnt[l / g]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}