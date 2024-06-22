#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1981A

//note the strange constraint that 2 * l <= r. This makes it so that there always exists a power of 2 in the range [l, r]. 
//it just so happens that if you pick that power of 2, it maximizes the score. 
//(proof is left to the reader)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int l, r;
        cin >> l >> r;
        int ans = 0;
        int x = 1;
        while(x * 2 <= r) {
            x *= 2;
            ans ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}