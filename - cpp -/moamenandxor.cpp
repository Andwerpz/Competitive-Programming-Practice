#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1557C

//observe that we can group the bits by their values, and take them seperately. 

//we can always take an even amount of bits for any group without increasing the xor value. 

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

void fac_init() {
    fac = vector<ll>(1e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    return divide(fac[n], mul(fac[k], fac[sub(n, k)]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    fac_init();
    while(t--){
        ll n, k;
        cin >> n >> k;
        ll ans = 0;
        if(n % 2 == 0) {
            ll ecomb = 0;
            ll bcomb = power((ll) 2, n);
            for(int i = 0; i < n; i += 2){
                ecomb = add(ecomb, nck(n, i));
            }
            for(int i = k - 1; i >= 0; i--){
                ans = add(ans, mul(power(ecomb, k - i - 1), power(bcomb, i)));
            }
            ans = add(ans, power(ecomb, k));
        }
        else {
            for(int i = 0; i < n; i += 2){
                ans = add(nck(n, i), ans);
            }
            ans = add(ans, 1);
            ans = power(ans, k);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
