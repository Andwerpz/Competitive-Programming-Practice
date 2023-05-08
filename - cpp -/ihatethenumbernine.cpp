#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 F

//for the most significant digit, or the nth digit of the number, you only have 8 options, 1 - 9. 

//for all the rest of the digits, you have 9 options, 0 - 9. 

//just compute 9 ^ (n - 1) * 8. 

ll mod = 1e9 + 7;

ll power(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = power(a, b / 2);
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
        ll n;
        cin >> n;
        ll ans = power(9, n - 1) * 8;
        ans %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}
