#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1761A

//note that if a + b >= n, then it has to be the case that a = n and b = n. 
//so either a = n and b = n, or a + b <= n - 2 (to leave a gap). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, a, b;
        cin >> n >> a >> b;
        if((a == n && b == n) || n - a - b >= 2){
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }
    
    return 0;
}