#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC 03-01-24 Div.2 - A

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    pair<int, int> ans;
    int tall = -1;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            if(s[j] == '.') {
                continue;
            }
            int val = s[j] - '0';
            if(val > tall){
                tall = val;
                ans = {i + 1, j + 1};
            }
        }
    }
    cout << ans.first << " " << ans.second << "\n";
    
    return 0;
}
