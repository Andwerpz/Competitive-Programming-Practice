#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<ld> vd;
// typedef __int128 lll;
// typedef __float128 lld;

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

//solves the following system of congruences for x:
//x === a_1 % m_1
//x === a_2 % m_2
// ...
//x === a_n % m_n
//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
ll chinese_remainder_theorem(vector<ll> modulo, vector<ll> remainder) {
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

//totient[i] or phi[i] = number of integers x where x < i and gcd(i, x) = 1. 
//useful properties:
//\sum_{d|n} phi(d) = n
//\sum_{d|n} phi(d) (n / d) = \sum_{i = 1}^{n} gcd(i, n)
//runs in n * log(log(n)) time. 
vector<ll> totient;
void calc_totient(int n) {
    totient = vector<ll>(n + 1, 0);
    for (int i = 0; i <= n; i++)
        totient[i] = i;

    for (int i = 2; i <= n; i++) {
        if (totient[i] == i) {
            for (int j = i; j <= n; j += i)
                totient[j] -= totient[j] / i;
        }
    }
}

//m(1) = 1
//m(p^k) = (k == 0) - (k == 1)
//m(xy) = m(x) m(y) if gcd(x, y) = 1
//f(n) = \sum_{d|n} g(d) 
//g(n) = \sum_{d|n} m(d) f(d)
//\sum_{d|n} m(d) = (n == 1)
vector<ll> mobius;
void calc_mobius(int n) {
    mobius = vector<ll>(n + 1, 0);
    mobius[1] = 1;
    vector<bool> c(n + 1, false);
    vector<ll> p(0);
    for(int i = 2; i <= n; i++){
        if(!c[i]) {
            p.push_back(i);
            mobius[i] = -1;
        }
        for(int j = 0; j < p.size() && i * p[j] <= n; j++){
            c[i * p[j]] = true;
            if(i % p[j] == 0){
                mobius[i * p[j]] = 0;
                break;
            }
            else {
                mobius[i * p[j]] = mobius[i] * mobius[p[j]];
            }
        }
    }
}

//harmonic series approximation
//H_n = ln(n) + \gamma
//approximation gets better as N grows, so precompute H for small n. 
vd H;
void init_H() {
    H = vd(100000000);
    H[0] = 0;
    for(int i = 1; i < H.size(); i++){
        H[i] = H[i - 1] + (ld) 1.0 / (ld) i;
    }
}

ld calc_H(ll n) {
    if(n < H.size()) {
        return H[n];
    }
    return log(n) + 0.57721566490153286060651;
}