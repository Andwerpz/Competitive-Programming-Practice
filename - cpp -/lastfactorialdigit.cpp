#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - G

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = 1;
        for(int i = 2; i <= n; i++){
            ans = (ans * i) % 10;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
