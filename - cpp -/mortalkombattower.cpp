#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) F

//relatively simple dp. 
//you just have to have an extra state keeping track of whether or not it's your friends turn. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> dp(n + 2, vector<int>(2, n + 1));
        //0 is friend, 1 is you
        dp[0][0] = 0;
        for(int i = 0; i < n; i++){
            //friend
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + a[i]);
            dp[i + 2][1] = min(dp[i + 2][1], dp[i][0] + a[i] + a[i + 1]);
            //you
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1]);
            dp[i + 2][0] = min(dp[i + 2][0], dp[i][1]);
        }
        cout << min(dp[n][0], dp[n][1]) << "\n";
    }
    
    return 0;
}
