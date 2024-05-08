#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1934A

//just sort and pick the extreme values. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
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
        int ans = 0;
        ans += abs(a[0] - a[a.size() - 1]);
        ans += abs(a[a.size() - 1] - a[1]);
        ans += abs(a[1] - a[a.size() - 2]);
        ans += abs(a[a.size() - 2] - a[0]);
        cout << ans << "\n";
    }
    
    return 0;
}
