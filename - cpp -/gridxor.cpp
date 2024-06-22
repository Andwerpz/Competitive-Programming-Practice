#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1628C

//why is this rated 2300? this is just constructive
//i just found a pattern on the board that takes each cell exactly once

//ig one observation is that since the board is bipartite, you can solve for half of the tiles at once, then
//mirror your solution and automatically get the other half.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> a(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> a[i][j];
            }
        }
        vector<vector<bool>> v(n, vector<bool>(n, false));
        for(int i = 0; i < n; i += 4) {
            int r = 0;
            int c = i;
            while(r < n && c >= 0){
                v[r][c] = true;
                r += 2;
                c -= 2;
            }
        }
        for(int i = 0; i < n; i++){
            int r = i;
            int c = n - 1;
            if((r + c) % 4 != 0){
                continue;
            }
            while(r < n && c >= 0){
                v[r][c] = true;
                r += 2;
                c -= 2;
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(v[i][j]) {
                    ans ^= a[i][j];
                }
                if(v[n - 1 - i][j]) {
                    ans ^= a[i][j];
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}