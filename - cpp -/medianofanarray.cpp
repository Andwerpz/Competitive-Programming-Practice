#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1946A

//bruh, check definition of median for the problem before attempting to solve. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int ind = n / 2 - (n % 2 == 0);
        int ans = 0;
        for(int i = ind; i < n; i++){
            if(a[i] != a[ind]) {
                break;
            }
            ans ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
