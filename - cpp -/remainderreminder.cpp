#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Kattis - remainderreminder

//direct application of chinese remainder theorem. 

//in this problem, the divisors are not necessarily pairwise coprime, but since a solution is guaranteed, 
//we can just take the top power for each unique prime factor, and use those as our divisors, along with
//the remainders. 

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

vector<ll> find_prime_factors(ll val) {
    if(val >= lp.size()) {
        return {};
    }
    vector<ll> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

ll mod = 1e9 + 7;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = power(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init() {
    fac = vector<ll>(1e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    ll ans = divide(fac[n], mul(fac[k], fac[sub(n, k)]));
    nckdp.insert({{n, k}, ans});
    return ans;
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
ll cantor(ll a, ll b, ll m) {
    return ((a + b) * (a + b + 1) / 2 + b) % m;
}

//returns the number of integers in the range [1, n] that are coprime with n. 
//runs in O(sqrt(n))
ll euler_phi(ll n) {
    ll result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

//modular inverse of a for any mod m. 
//if -1 is returned, then there is no solution. 
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
ll chinese_remainder_theorem(vector<ll>& modulo, vector<ll>& remainder) {
    if(modulo.size() != remainder.size()) {
        return -1;
    }
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    prime_sieve(2e6);
    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;
    //find the largest volumes
    vector<ll> v(0);
    for(ll i = 1; min(a - i * 2, b - i * 2) > 0; i++){
        ll l = a - i * 2;
        ll w = b - i * 2;
        ll h = i;
        //cout << l << " " << w << " " << h << endl;
        v.push_back(l * w * h);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<ll> rem = {c, d, e};
    map<ll, pair<ll, ll>> m;    //for each factor, map the largest factor 
    for(int i = 0; i < 3; i++){
        //cout << v[i] << "\n";
        vector<ll> factors = find_prime_factors(v[i]);
        for(int j = 0; j < factors.size(); j++){
            ll fac = factors[j];
            while(v[i] % fac == 0){
                fac *= factors[j];
            }
            fac /= factors[j];
            if(m.find(factors[j]) == m.end()) {
                m.insert({factors[j], {fac, rem[i]}});
            }
            if(m[factors[j]].first < fac) {
                m[factors[j]] = {fac, rem[i]};
            }
        }
    }
    vector<ll> modulo(0);
    vector<ll> remainder(0);
    //cout << "CONGRUENCES : " << "\n";
    for(auto i = m.begin(); i != m.end(); i++){
        //cout << i -> second.second << " " << i -> second.first << "\n";
        modulo.push_back(i -> second.first);
        remainder.push_back(i -> second.second);
    }    
    ll crem = chinese_remainder_theorem(modulo, remainder);
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    //cout << "M : " << M << "\n";
    //cout << "CREM : " << crem << "\n";
    ll ans = (f / M) * M + crem;
    if(ans < f){
        ans += M;
    }
    cout << ans << "\n";
    
    return 0;
}
