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
const ll mod = 998244353;

//2025 NAQ - G

ll binexp(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while(b) {
        if(b & 1) {
            res = (res * a) % mod;
        }
        b /= 2;
        a = (a * a) % mod;
    }
    return res;
}

ll inv(ll x) {
    return binexp(x, mod - 2);
}

const int maxn = 1e5 + 1;
ll fac [maxn], inv_fac[maxn];

void init_fac() {
    fac[0] = 1;
    inv_fac[0] = 1;
    for(int i = 1; i < maxn; i++) {
        fac[i] = (fac[i - 1] * i) % mod;
        inv_fac[i] = inv(fac[i]);
    }
}

ll nck(ll n, ll k) {
    if(k < 0 || k > n) return 0;
    return fac[n] * inv_fac[k] % mod * inv_fac[n - k] % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    init_fac();
    ll n, k; cin >> n >> k;

    cout << n * (2 * k + 1) % mod * inv(2 * k + 1) % mod * binexp((2 * k * inv(2 * k + 1) % mod), 2 * k) % mod << '\n';
    
    return 0;
}