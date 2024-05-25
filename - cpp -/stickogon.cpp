#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1957A

//just group all the same size sticks into triangles. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        map<int, int> m;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            m[a] ++;
        }
        int ans = 0;
        for(auto i = m.begin(); i != m.end(); i++){
            ans += i -> second / 3;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
