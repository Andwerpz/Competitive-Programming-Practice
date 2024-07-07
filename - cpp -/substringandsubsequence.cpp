#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1989B

//you want to use as many letters from a to account for b. Since the lengths are only 100, you can 
//just brute force the maximum number of letters to use. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string a, b;
        cin >> a >> b;
        int ans = 1e7;
        for(int i = 0; i < b.size(); i++){
            int cans = i;
            int bptr = i;
            for(int j = 0; j < a.size(); j++){
                if(bptr != b.size() && a[j] == b[bptr]) {
                    bptr ++;
                }
            }
            cans += a.size() + b.size() - bptr;
            ans = min(ans, cans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}