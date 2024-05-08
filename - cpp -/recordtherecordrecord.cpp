#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Spring 2024 Open Contest - J

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 0;
    set<int> v;
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;
        int c_ans = 0;
        for(int j = 0; j < m; j++){
            int next;
            cin >> next;
            if(!v.count(next)) {
                c_ans ++;
                v.insert(next);
            }
        }
        ans = max(ans, c_ans);
    }
    cout << ans << "\n";
    
    return 0;
}
