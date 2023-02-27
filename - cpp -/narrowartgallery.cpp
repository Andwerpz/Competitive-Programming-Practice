#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 06 B

//3 state dp:
//how many rooms blocked 
//which row
//state of prev row; 0 : nothing blocked, 1 : left blocked, 2 : right blocked

//keep track of minimum sum of blocked rooms. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(2, 0));
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1];
        sum += a[i][0] + a[i][1];
    }
    //how many rooms blocked
    //row
    //state of prev row; 0 : nothing blocked, 1 : left blocked, 2 : right blocked
    //minimum sum of blocked rooms
    vector<vector<vector<ll>>> dp(k + 1, vector<vector<ll>>(n + 1, vector<ll>(3, 1000000000)));
    dp[0][0][0] = 0;
    for(int i = 0; i <= k; i++){
        for(int j = 1; j <= n; j++){
            //cout << i << " " << j << "\n";
            //don't block anything
            dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][0]);
            dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][1]);
            dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][2]);

            if(i != 0){
                //block left
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][0] + a[j - 1][0]);
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][1] + a[j - 1][0]);
                //block right
                dp[i][j][2] = min(dp[i][j][2], dp[i - 1][j - 1][0] + a[j - 1][1]);
                dp[i][j][2] = min(dp[i][j][2], dp[i - 1][j - 1][2] + a[j - 1][1]);
            }
            //cout << dp[i][j][0] << " " << dp[i][j][1] << " " << dp[i][j][2] << "\n";
        }
    }
    cout << sum - min(dp[k][n][0], min(dp[k][n][1], dp[k][n][2])) << "\n";
    
    return 0;
}
