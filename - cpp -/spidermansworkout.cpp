#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 06 D

//dp with solution construction. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<ll>> dp(n + 1, vector<ll>(1000, INT32_MAX));
        vector<vector<char>> prev(n + 1, vector<char>(1000, 0));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            ll move = a[i - 1];
            for(int j = 0; j < 1000; j++){
                char ud = 0;
                if(j - move >= 0) {
                    if(dp[i][j] > max(dp[i - 1][j - move], (ll) j)){
                        ud = 'U';
                        dp[i][j] = max(dp[i - 1][j - move], (ll) j);
                    }
                }
                if(j + move < 1000) {
                    if(dp[i][j] > dp[i - 1][j + move]) {
                        ud = 'D';
                        dp[i][j] = dp[i - 1][j + move];
                    }
                }
                prev[i][j] = ud;
            }
        }
        if(prev[n][0] == 0){
            cout << "IMPOSSIBLE\n";
        }
        else {
            int ind = 0;
            string ans = "";
            for(int i = n; i >= 1; i--){
                ans += prev[i][ind];
                if(prev[i][ind] == 'U'){
                    ind -= a[i - 1];
                }
                else {
                    ind += a[i - 1];
                }
            }
            reverse(ans.begin(), ans.end());
            cout << ans << "\n";
        }
    }
    
    return 0;
}
