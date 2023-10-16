#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 2220

//classic digit dp problem. 

ll solve(ll a) {
    if(a == -1){
        return 0;
    }
    vector<int> d(0);
    while(a != 0){
        d.push_back(a % 10);
        a /= 10;
    }
    reverse(d.begin(), d.end());
    //i : which digit
    //j : what is the previous digit
    //k : tight?
    vector<vector<vector<ll>>> dp(d.size() + 1, vector<vector<ll>>(10, vector<ll>(2, 0)));
    dp[0][0][1] = 1;
    for(int i = 1; i <= d.size(); i++){
        dp[i][0][0] = 1;
    }
    for(int i = 0; i < d.size(); i++){
        for(int j = 0; j < 10; j++){
            //tight
            //maintain tight
            if(d[i] != j) {
                dp[i + 1][d[i]][1] += dp[i][j][1];
            }
            //don't maintain tight
            for(int k = 0; k < d[i]; k++){
                if(k == j){
                    continue;
                }
                dp[i + 1][k][0] += dp[i][j][1];
            }
            //not tight
            for(int k = 0; k < 10; k++){
                if(k == j){
                    continue;
                }
                dp[i + 1][k][0] += dp[i][j][0];
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 10; i++){
        ans += dp[d.size()][i][0];
        ans += dp[d.size()][i][1];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << "\n";
    
    return 0;
}
