#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll mod = 1e9 + 7;

ll pow(ll a, ll b){
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans *= ans;
    ans %= mod;
    if(b % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

ll divide(ll a, ll b){
    return (a * pow(b, mod - 2)) % mod;
}

ll fac(ll a) {
    ll ans = 1;
    for(int i = 2; i <= a; i++){
        
    }
}

ll nck(ll n, ll k) {
    return 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}
