#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1814B

//lets say that the maximum length your legs are going to ever be is x. 
//you can compute the minimum amount of steps to travel to (a, b) in constant time given x. 

//then, just brute force all values of x to 10^6. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll a, b;
        cin >> a >> b;
        ll ans = 1e18;
        for(ll i = 1; i < 1e6; i++){
            ll cans = a / i + (a % i != 0) + b / i + (b % i != 0) + i - 1;
            ans = min(ans, cans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
