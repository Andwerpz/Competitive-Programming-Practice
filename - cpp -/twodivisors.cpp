#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1916B

//I just guessed that if b isn't a multiple of a, we just find the lcm. Otherwise, the answer is
//b^2 / a. 

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll a, b;
        cin >> a >> b;
        ll g = gcd(a, b);
        a /= g;
        b /= g;
        ll ans = a * b;
        if(a == 1){
            ans = b * b;
        }
        ans *= g;
        cout << ans << "\n";
    }
    
    return 0;
}
