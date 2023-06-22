#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll mod = 1e9 + 7;
vector<ll> fac;

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    if(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll pow(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, pow(b, mod - 2));
}

void fac_init() {
    fac = vector<ll>(1e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    return divide(fac[n], mul(fac[k], fac[sub(n, k)]));
}
