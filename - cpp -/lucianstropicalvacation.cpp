#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 C

//for each day, store what activity he did on the previous day. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(3));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            cin >> a[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    for(int i = 0; i < n; i++){
        //you did the first one
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + a[i][1]);
        dp[i + 1][2] = max(dp[i + 1][2], dp[i][0] + a[i][2]);
        //you did the second one
        dp[i + 1][2] = max(dp[i + 1][2], dp[i][1] + a[i][2]);
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][1] + a[i][0]);
        //you did the third one
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][2] + a[i][0]);
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][2] + a[i][1]);
    }
    cout << max({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
    
    return 0;
}
