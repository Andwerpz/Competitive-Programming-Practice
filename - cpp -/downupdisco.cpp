#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 01-26-24 Div. 2 - F

//you only need to flip any tile once. Just go from the bottom left corner and start flipping when necessary. 

//to keep track of how many times a tile should be flipped so far, we can propogate the flips towards the top left
//corner, using a 2D prefix sum like technique. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            g[i][j] = s[j] == '1';
        }
    }
    int ans = 0;
    vector<vector<bool>> f(n, vector<bool>(m, false));
    for(int i = n - 1; i >= 0; i--){
        for(int j = m - 1; j >= 0; j--){
            if(g[i][j] ^ f[i][j]) {
                ans ++;
                f[i][j] = f[i][j] ^ true;
            }
            if(i != 0){
                f[i - 1][j] = f[i - 1][j] ^ f[i][j];
            }
            if(j != 0){
                f[i][j - 1] = f[i][j - 1] ^ f[i][j];
            }
            if(i != 0 && j != 0){
                f[i - 1][j - 1] = f[i - 1][j - 1] ^ f[i][j];
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
