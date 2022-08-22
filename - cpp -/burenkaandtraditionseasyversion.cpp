#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1719D1

//any operation of length greater than 2 is un-necessary. 

//dp[n][k] will hold the minimum time required to make all a[i] = 0 where i < k, and a[n] = k. 

//at dp[i][j], you can either just xor a[i] with a[i], or xor a[i] and a[i + 1] with a[i]. 

//this works since the xor operation will propogate when you do a length 2 operation, and it will
//not propogate when you do a length 1 operation. You're pretty much just trying all possibilities of
//propogating xor, or not propogating xor. 

//max value of k is 8191, or 2^13 - 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> dp(n + 1, vector<int>(8192, -1));
        dp[0][a[0]] = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 8192; j++){
                if(dp[i][j] == -1){
                    continue;
                }
                if(dp[i + 1][a[i + 1]] == -1){
                    dp[i + 1][a[i + 1]] = dp[i][j] + (j != 0? 1 : 0);
                }
                dp[i + 1][a[i + 1]] = min(dp[i + 1][a[i + 1]], dp[i][j] + (j != 0? 1 : 0));
                int addX = a[i + 1] ^ j;
                if(dp[i + 1][addX] == -1){
                    dp[i + 1][addX] = dp[i][j] + (j != 0? 1 : 0);
                }
                dp[i + 1][addX] = min(dp[i + 1][addX], dp[i][j] + (j != 0? 1 : 0));
            }
        }
        int ans = dp[n][0];
        for(int i = 0; i < 8192; i++){
            if(dp[n][i] == -1){
                continue;
            }
            ans = min(ans, dp[n][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
