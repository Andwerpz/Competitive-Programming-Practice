
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1746

//simple dp problem. Save a dp state for each different value at each index. dp[n][m].
//how many different arrays are possible ending with value m with length n. 

//to update, if there is no specified value for a given i, then dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + dp[i - 1][j + 1].
//since there is no specified value, you can do it for all values.

//if there is a specified value, then you can only do it for that value. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    long mod = 1e9 + 7;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        nums[i] --;
    }
    vector<vector<long>> dp(n);
    for(int i = 0; i < n; i++){
        dp[i] = vector<long>(m);
    }
    if(nums[0] == -1){
        for(int i = 0; i < m; i++){
            dp[0][i] = 1;
        }
    }
    else{
        dp[0][nums[0]] = 1;
    }
    for(int i = 1; i < n; i++){
        if(nums[i] == -1){
            for(int j = 0; j < m; j++){
                dp[i][j] = dp[i - 1][j];
                if(j > 0){
                    dp[i][j] += dp[i - 1][j - 1];
                }
                if(j < m - 1){
                    dp[i][j] += dp[i - 1][j + 1];
                }
                while(dp[i][j] >= mod){
                    dp[i][j] -= mod;
                }
            }
        }
        else{
            dp[i][nums[i]] = dp[i - 1][nums[i]];
            if(nums[i] > 0){
                dp[i][nums[i]] += dp[i - 1][nums[i] - 1];
            }
            if(nums[i] < m - 1){
                dp[i][nums[i]] += dp[i - 1][nums[i] + 1];
            }
            while(dp[i][nums[i]] >= mod){
                dp[i][nums[i]] -= mod;
            }
        }
    }
    long ans = 0;
    for(int i = 0; i < m; i++){
        ans += dp[n - 1][i];
    }
    cout << (ans % mod) << endl;
    
    return 0;
}
