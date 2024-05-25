#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1973A

//first, if a + b + c is not divisible by 2, then the score is invalid. 
//otherwise, it's always possible

//first, equalize a and b by taking from b and c. 
//then, equally take from c using a and b
//if after this, a and b != 0, then just match between a and b. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b, c;
        cin >> a >> b >> c;
        if((a + b + c) % 2 == 1){
            cout << "-1\n";
            continue;
        }
        int ans = 0;
        int diff = b - a;
        ans += diff;
        b -= diff;
        c -= diff;
        int left = c / 2;
        left = min(left, a);
        ans += left * 2;
        a -= left;
        b -= left;
        c -= 2 * left;
        ans += a;
        cout << ans << "\n";
    }
    
    return 0;
}
