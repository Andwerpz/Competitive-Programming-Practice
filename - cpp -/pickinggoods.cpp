#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c, t;
    cin >> r >> c >> t;
    vector<vector<ll>> a(r, vector<ll>(c, 0));
    for(int i = 0; i < t; i++){
        int row, col, val;
        cin >> row >> col >> val;
        row --;
        col --;
        a[row][col] = val;
    }
    vector<vector<vector<ll>>> dp(r, vector<vector<ll>>(c, vector<ll>(4, 0)));
    //move, then take
    //move, then don't take
    dp[0][0][1] = a[0][0];
    ll ans = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            for(int k = 0; k < 4; k++){
                //move, and don't take
                //right
                if(j != c - 1) {
                    dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k]);
                }
                //down
                if(i != r - 1){
                   dp[i + 1][j][0] = max(dp[i + 1][j][0], dp[i][j][k]); 
                }
                //move then take
                //right
                if(j != c - 1 && k != 3) {
                    dp[i][j + 1][k + 1] = max(dp[i][j + 1][k + 1], dp[i][j][k] + a[i][j + 1]);
                }
                //down
                if(i != r - 1){
                    dp[i + 1][j][1] = max(dp[i + 1][j][1], dp[i][j][k] + a[i + 1][j]);
                }
                if(i == r - 1 && j == c - 1){
                    ans = max(ans, dp[i][j][k]);
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
