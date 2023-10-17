#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - anthony

//dp with probability

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<ld>> dp(n + 1, vector<ld>(m + 1, 0));
    dp[n][m] = 1;
    for(int i = n + m; i >= 2; i--){
        ld prob;
        cin >> prob;
        for(int j = 1; j <= n; j++){
            int c_a = j;
            int c_b = i - j;
            if(c_b > m || c_b <= 0) {
                continue;
            }
            //anthony wins
            dp[c_a][c_b - 1] += dp[c_a][c_b] * prob;
            //cora wins
            dp[c_a - 1][c_b] += dp[c_a][c_b] * (1.0 - prob);
        }
    }
    ld ans = 0;
    for(int i = 1; i <= n; i++){
        ans += dp[i][0];
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
