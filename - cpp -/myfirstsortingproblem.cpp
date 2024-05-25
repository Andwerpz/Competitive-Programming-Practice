#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1971A

//just meeting the daily quota

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x, y;
        cin >> x >> y;
        cout << min(x, y) << " " << max(x, y) << "\n";
    }
    
    return 0;
}
