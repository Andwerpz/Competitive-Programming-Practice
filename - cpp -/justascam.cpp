#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;

ll mul(ll a, ll b){
    return (a * b) % mod;
}

ll pow(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1){
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    ll invB = pow(b, mod - 2);
    return mul(a, invB);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<ll> factorial(2e5);
    factorial[0] = 1;
    for(int i = 1; i < factorial.size(); i++){
        factorial[i] = mul(factorial[i - 1], (ll)i);
    }
    ll n, p;
    cin >> n >> p;
    ll ans = 1;
    ll cnt = 1;
    while(n >= p) {
        ll m = n - p >= p? p : p - 1;
        ans += divide(mul(divide(factorial[n], mul(factorial[p], factorial[n - p])), m), cnt);
        n -= p;
        cnt ++;
    }
    if(n != 0){
        ans = mul(ans, n);
    }
    ans += 1;
    cout << ans << "\n";
    
    return 0;
}
