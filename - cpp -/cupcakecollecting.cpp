#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - E

//standard grid dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> g[i][j];
        }
    }
    vector<vector<int>> dp(n, vector<int>(n, -1));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(g[i][j] == -1){
                continue;
            }
            if(i != 0 && dp[i - 1][j] != -1){
                dp[i][j] = max(dp[i - 1][j] + g[i][j], dp[i][j]);
            }
            if(j != 0 && dp[i][j - 1] != -1){
                dp[i][j] = max(dp[i][j - 1] + g[i][j], dp[i][j]);
            }
        }
    }
    cout << dp[n - 1][n - 1] << "\n";
    
    return 0;
}
