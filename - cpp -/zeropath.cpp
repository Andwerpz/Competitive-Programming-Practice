#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1695C

//notice that the path length is always equal to n + m - 1. If this value isn't even
//then it is impossible to construct a path that will sum to 0. 

//if n is even, then we can use a dp solution. 

//dp[i][j][0] = min path sum ending at (i, j)
//dp[i][j][1] = max path sum ending at (i, j). 

//since g[i][j] is -1 or 1, that means that we can construct every other number within dp[i][j][0] to dp[i][j][1]. 

//all we need to do is to check if dp[n - 1][m - 1][0] and dp[n - 1][m - 1][1] contains 0. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(m));
        vector<vector<int>> g(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){ 
                cin >> g[i][j];
                dp[i][j].first = 1e9;
                dp[i][j].second = -1e9;
            }
        }
        dp[0][0].first = g[0][0];
        dp[0][0].second = g[0][0];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++){
                if(i != 0) {
                    dp[i][j].first = min(dp[i][j].first, dp[i - 1][j].first + g[i][j]);
                    dp[i][j].second = max(dp[i][j].second, dp[i - 1][j].second + g[i][j]);
                }
                if(j != 0){
                    dp[i][j].first = min(dp[i][j].first, dp[i][j - 1].first + g[i][j]);
                    dp[i][j].second = max(dp[i][j].second, dp[i][j - 1].second + g[i][j]);
                }
                //cout << dp[i][j].first << " " << dp[i][j].second << " | ";
            }
            //cout << endl;
        }
        if(dp[n - 1][m - 1].first <= 0 && 0 <= dp[n - 1][m - 1].second && (n + m) % 2 == 1){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
    
    return 0;
}
