#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

ll func(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    if(b == 1){
        return a;
    }
    ll ans = func(a, b / 2);
    ans *= ans;
    ans %= mod;
    if(b % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll a, b, c;
        cin >> a >> b >> c;
        cout << func(a, func(b, c)) << "\n";
    }
    
    return 0;
}

