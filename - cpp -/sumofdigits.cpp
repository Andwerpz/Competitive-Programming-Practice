#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//SPOJ - CPCRC1C

//classic digit dp problem

//for each length of number, count how many of each digit sum we can make. 

//note that an upper bound on the max digit sum is just the number of digits in the max * 10. 

ll solve(int val) {
    string max = to_string(val);
    int n = max.size();
    int msum = max.size() * 10;
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(msum, vector<ll>(2, 0)));
    dp[0][0][1] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < msum; j++){
            //tight
            {
                int dig = max[i] - '0';
                //maintain tight
                if(j + dig < msum) {
                    dp[i + 1][j + dig][1] += dp[i][j][1];
                }
                //don't maintain
                for(int k = 0; k < dig; k++){
                    if(j + k >= msum) {
                        break;
                    }
                    dp[i + 1][j + k][0] += dp[i][j][1];
                }
            }
            //not tight
            for(int k = 0; k < 10; k++){
                if(j + k >= msum) {
                    break;
                }
                dp[i + 1][j + k][0] += dp[i][j][0];
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < msum; i++) {
        ans += (dp[n][i][0] + dp[n][i][1]) * i;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    cin >> a >> b;
    while(a != -1) {
        cout << solve(b) - solve(a - 1) << "\n";
        cin >> a >> b;
    }
    
    return 0;
}
