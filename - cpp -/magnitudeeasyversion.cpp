#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984C1

//I observed that any process which creates the maximum has to follow this pattern:
//1. we initially perform some number of type 1 operations. 
//2. then for the remaining suffix, we perform only type 2 operations. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<ll> pfx(n);
        for(int i = 0; i < n; i++){
            pfx[i] = a[i];
            if(i != 0){
                pfx[i] += pfx[i - 1];
            }
        }
        ll cmax = abs(a[0]);
        for(int i = 1; i < n; i++){
            cmax = max(abs(cmax + a[i]), abs(pfx[i - 1] + a[i]));
        }
        cout << cmax << "\n";
    }
    
    return 0;
}