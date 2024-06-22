#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1979B

//in the contest, i solved this one just by noticing that the amount common is just equal to the first bit that
//is different beteen x and y. 

//intuitively, this is because you can use i and j to match anything beyond the first unequal bit, 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll x, y;
        cin >> x >> y;
        ll ans = 1;
        for(int i = 0; i < 30; i++){
            if((x & (1 << i)) != (y & (1 << i))) {
                break;
            }
            ans *= 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}