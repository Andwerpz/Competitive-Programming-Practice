#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll mod = 1e9 + 7;
vector<vector<int>> rem;

ll add(ll a, ll b) {
    ll ret = a + b;
    if(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll solve(string max, int m, int d) {
    int n = max.size();
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(m, vector<ll>(2, 0)));
    dp[0][0][1] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool even = i % 2 == 0;
            int dig = max[i] - '0';
            if(even) {
                //next number must be not d
                //tight
                if(dig != d) {
                    dp[i + 1][(j + rem[i][dig]) % m][1] = add(dp[i + 1][(j + rem[i][dig]) % m][1], dp[i][j][1]);
                }
                for(int k = 0; k < dig; k++){
                    if(k == d) {
                        continue;
                    }
                    dp[i + 1][(j + rem[i][k]) % m][0] = add(dp[i + 1][(j + rem[i][k]) % m][0], dp[i][j][1]);
                }
                //not tight
                for(int k = 0; k < dig; k++){
                    if(k == d){
                        continue;
                    }
                    dp[i + 1][(j + rem[i][k]) % m][0] = add(dp[i + 1][(j + rem[i][k]) % m][0], dp[i][j][0]);
                }
            }
            else {
                //next number must be d
                //tight
                if(dig == d) {
                    dp[i + 1][(j + rem[i][d]) % m][1] = add(dp[i + 1][(j + rem[i][d]) % m][1], dp[i][j][1]);
                }
                else if(dig < d){
                    dp[i + 1][(j + rem[i][d]) % m][0] = add(dp[i + 1][(j + rem[i][d]) % m][0], dp[i][j][1]);
                }
                //not tight
                dp[i + 1][(j + rem[i][d]) % m][0] = add(dp[i + 1][(j + rem[i][d]) % m][0], dp[i][j][0]);
            }
        }
    }
    return add(dp[n][0][0], dp[n][0][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, d;
    cin >> m >> d;
    string a, b;
    cin >> a >> b;
    rem = vector<vector<int>>(a.size(), vector<int>(10, 0));
    for(int i = 0; i < 10; i++){
        rem[a.size() - 1][i] = i % m;
    }
    for(int i = a.size() - 1; i >= 1; i--){
        for(int j = 0; j < 10; j++){
            rem[i - 1][j] = (rem[i][j] * 10) % m;
        }
    }
    
    return 0;
}
