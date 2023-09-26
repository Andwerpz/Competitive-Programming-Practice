#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

//modular inverse of a for any mod m. 
ll mod_inv(ll a, ll m) {
    return power(a, euler_phi(m) - 1);
}

//
ll chinese_remainder_theorem(vector<ll>& modulo, vector<ll>& remainder) {
    if(modulo.size() != remainder.size()) {
        throw invalid_argument("modulo and remainder must be the same size");
    }
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(modulo[i], M_i);
        solution = (solution + (a_i * M_i) % M * N_i) % M;
    }
    return solution;
}

void make_co(ll& a, ll& b) {
    ll g = gcd(a, b);
    a /= g;
    b /= g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;
    //find the largest volumes
    vector<ll> v(0);
    for(ll i = 1; i < min(a / 2, b / 2); i++){
        ll l = a - i * 2;
        ll w = b - i * 2;
        ll h = i;
        cout << l << " " << w << " " << h << endl;
        v.push_back(l * w * h);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<ll> modulo = {v[0], v[1], v[2]};
    vector<ll> remainder = {c, d, e};
    make_co(modulo[0], modulo[1]);
    make_co(modulo[1], modulo[2]);
    make_co(modulo[2], modulo[0]);
    remainder[0] %= modulo[0];
    remainder[1] %= modulo[1];
    remainder[2] %= modulo[2];
    ll crem = chinese_remainder_theorem(modulo, remainder);
    ll M = modulo[0] * modulo[1] * modulo[2];
    cout << "M : " << M << "\n";
    cout << "CREM : " << crem << "\n";
    cout << "MOD : " << modulo[0] << " " << modulo[1] << " " << modulo[2] << "\n";
    ll ans = (f / M) * M;
    ans += M + crem;
    if(ans > g){
        ans -= M;
    }
    cout << ans << "\n";
    
    return 0;
}
