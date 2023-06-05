#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll mod = 1e9 + 7;

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
