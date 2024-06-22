#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1979A

//we just need to find the minimum maximum out of any subarray of length greater than 2. 
//then subtract 1. 

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
        int ans = 1e9;
        for(int i = 1; i < n; i++){
            ans = min(ans, max(a[i], a[i - 1]) - 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}