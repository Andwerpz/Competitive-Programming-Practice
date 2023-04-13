#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1777B

//if we concatenate a permutation to it's reverse, the resulting array will always have n * (n - 1) inversions, where
//n is the length of the permutation. 

//then, we just need to compute n! * n * (n - 1). 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    ll mod = 1e9 + 7;
    while(t-- > 0){
        ll n;
        cin >> n;
        ll ans = 1;
        for(ll i = 2; i <= n; i++){
            ans *= i;
            ans %= mod;
        }
        ans *= ((n - 1) * n) % mod;
        ans %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}
