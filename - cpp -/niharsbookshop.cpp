#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 G

//classic knapsack dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    vector<int> cost(n, 0);
    vector<int> val(n, 0);
    for(int i = 0; i < n; i++){
        cin >> cost[i];
    }
    for(int i = 0; i < n; i++){
        cin >> val[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    int ans = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= x; j++){
            if(j != x){
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            }
            if(i != n){
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                int next = j + cost[i];
                if(next <= x) {
                    dp[i + 1][next] = max(dp[i + 1][next], dp[i][j] + val[i]);
                }
            }
        }
    }
    cout << dp[n][x] << "\n";
    
    return 0;
}
