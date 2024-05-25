#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1665A

//after manipulating the equation we get: gcd(a, b) = cd / gcd(c, d)
// -> gcd(a, b) * gcd(c, d) = cd
//note that if we assign b, c, d = 1, then gcd(a, 1) * gcd(1, 1) = 1, which is true for any value of a >= 1

//thus, we just say a = n - 3, and b, c, d = 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        cout << n - 3 << " " << 1 << " " << 1 << " " << 1 << "\n";
    }
    
    return 0;
}
