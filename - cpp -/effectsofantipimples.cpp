#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1877D

//the maximum value among black and green pixels is determined by the choice of black pixels. 
//for each pixel, compute the maximum value if only that pixel is chosen. Then, the maximum value
//if multiple pixels are chosen is just the maximum of the aforementioned precomputed values of 
//those pixels. 

//for each possible maximum value, how many combinations of black pixels can be chosen so that 
//that value is the maximum?

//first, consider the minimum value that can be maximum. Let's say the count of pixels
//that have the value, 'v', as maximum is 'a'. We can pick exactly 2^a - 1 combinations 
//of these pixels, so that is obviously the answer. 

//then, let's consider the 2nd minimum value. The number of pixels with the 2nd minimum is 'b'
//so there are 2^b - 1 ways to pick the 2nd minimum, but we can also pick any combination of pixels
//from the minimum value, so there are actually (2^b - 1) * (2^a) ways to pick the 2nd minimum value. 

//in general, let 'a' be the amount of pixels of the current value, and 'b' be the amount of pixels
//below this value, the number of ways to pick pixels such that the answer is the current value is
//(2^a - 1) * (2^b). 

ll mod = 998244353;
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
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    map<ll, ll> mp;
    for(int i = 0; i < n; i++){
        ll mx = 0;
        for(int j = i; j < n; j += i + 1){
            mx = max(mx, a[j]);
        }
        if(mp.find(mx) == mp.end()){
            mp.insert({mx, 0});
        }
        mp[mx] ++;
    }
    ll ans = 0;
    ll nr_less = 0;
    for(auto i = mp.begin(); i != mp.end(); i++){
        ll cur = i -> first;
        ll amt = i -> second;
        ll nr_ways = sub(power(2, amt), 1);
        nr_ways = mul(nr_ways, power(2, nr_less));
        ans = add(ans, mul(nr_ways, cur));
        nr_less += amt;
    }
    cout << ans << "\n";
    
    return 0;
}
