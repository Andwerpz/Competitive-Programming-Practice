#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1780B

//lets say that the optimal solution is when k = 3, and gcd(b1, b2, b3) = g. We can see that if we merge
//the segments corresponding to b1 and b2, the new gcd(b1 + b2, b3) >= g. 

//from this, we can easily see that an optimal solution always exists when k = 2. 

//from there, you just need to do a linear search along the prefix and suffix sums. 

ll gcd(ll a, ll b) {
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll sum = 0;
        ll pfx = 0;
        for(int i = 0; i < n; i++){
            sum += a[i];
        }
        ll ans = 0;
        for(int i = 0; i < n - 1; i++) {
            pfx += a[i];
            sum -= a[i];
            ans = max(ans, gcd(pfx, sum));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
