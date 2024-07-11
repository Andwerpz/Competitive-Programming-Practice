#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 451E

//we can rewrite the problem as a generating function. We're trying to count the number of ways to pick from n buckets,
//s elements. So, naturally, our generating function should be 
//f(x) = (1 + x + x^2 + ... + x^f_1)(1 + x + x^2 + ... + x^f_2) ... (1 + x + x^2 + ... + x^f_n)
//and the answer we want is [x^s]f(x). 

//note that we can reduce the sequence 1 + x + x^2 + ... + x^n = (1 - x^(n + 1)) / (1 - x), so 
//f(x) = (1 - x^(f_1 + 1)) ... (1 - x^(f_n + 1)) * (1 - x)^-n

//since n is 20, the top will have only 2^20 elements, so we can just naively expand that. The bottom however is more 
//problematic, since it's on the bottom. 
//However, note that 1 / (1 - x) = 1 + x + x^2 + ...  Therefore, we can interpret (1 - x)^-n in a combinatorial sense. 
//(1 - x)^-n = (1 + x + x^2 + ...)^n = g(x) In this case, [x^k]g(x) is the number of ways we can write k as a sum
//of n non-negative integers. 

//if we imagine we have n - 1 + k elements, which are all initially bars, we can pick k of them to be stars, leaving
//n - 1 of them as bars, seperating the stars into n contiguous segments. Therefore, the number of ways to write k as a
//sum of n non-negative integers is nck(n - 1 + k, k). 

//Therefore, g(x) = sum of k -> infinity(x^k * nck(n + k - 1, k))
//From here, all we have to do is consider for each 'top' element, what power of x from the 'bottom' it needs to get
//to s. Note that if it's already over s, then it's impossible. 

ll mod = 1e9 + 7;
vector<ll> inv(100, 0);

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

//assumes that |n - k| is relatively small. 
ll nck(ll n, ll k) {
    if(k > n || k < 0){
        return 0;
    }
    k = min(k, n - k);
    ll ans = 1;
    for(int i = 0; i < k; i++){
        ans = (ans * ((n - i) % mod)) % mod;
        ans = (ans * inv[i + 1]) % mod;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    inv[0] = 1;
    for(int i = 1; i < 100; i++){
        inv[i] = mod_inv(i, mod);
    }
    ll n, s;
    cin >> n >> s;
    vector<ll> f(n);
    for(int i = 0; i < n; i++){
        cin >> f[i];
    }
    map<ll, ll> poly;
    poly[0] = 1;
    for(int i = 0; i < n; i++){
        ll pow = f[i] + 1;
        map<ll, ll> n_poly;
        for(auto j = poly.begin(); j != poly.end(); j++){
            ll cpow = j -> first;
            ll amt = j -> second;
            n_poly[cpow] += amt;
            n_poly[cpow + pow] -= amt;
            if(n_poly[cpow + pow] < 0) {
                n_poly[cpow + pow] += mod;
            }
            n_poly[cpow] %= mod;
        }
        poly = n_poly;
    }
    ll ans = 0;
    for(auto i = poly.begin(); i != poly.end(); i++){
        ll pow = i -> first;
        ll amt = i -> second;
        ll reqpow = s - pow;
        amt = (amt * nck(n + reqpow - 1, reqpow)) % mod;
        ans += amt;
        ans %= mod;
    }
    cout << ans << "\n";
    
    return 0;
}
