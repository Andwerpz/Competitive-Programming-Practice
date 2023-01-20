#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1767C

//i think i have the right idea, just need to work out some bugs. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(0));
    vector<vector<ll>> dp(n, vector<ll>(0));
    vector<vector<int>> t(n, vector<int>(0));
    vector<int> lastOne(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++){
            int next;
            cin >> next;
            a[i].push_back(next);
            dp[i].push_back(0);
            t[i].push_back(0);
            if(a[i][j] == 2){
                t[i][j] ++;
            }
            if(a[i][j] == 1) {
                lastOne[i] = j;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(i > 0){
                t[j][i] += t[j][i - 1];
                t[j][i] += t[j + 1][i - 1];
            }
            if(i > 1) {
                t[j][i] -= t[j + 1][i - 2];
            }
        }
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n - i; j++){
    //         cout << t[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    ll ans = 0;
    ll mod = 998244353;
    dp[0][0] = 2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++) {
            if(j == 0 && a[i][j] == 2){
                dp[i][j] = 0;
            }
            //same char
            if(j != n - i - 1 && a[i][j + 1] != 2) {
                dp[i][j + 1] += dp[i][j];
                dp[i][j + 1] %= mod;
            }
            //different char
            if(i + 1 + j >= n) {    //trying to make a string of length higher than n. 
                continue;
            }
            int num2 = 0;
            if(j != 0){
                num2 = t[i + 1][j - 1];
            }
            bool noSkip1 = true;
            int p = 0;
            for(int k = j; k >= 0; k--) {
                noSkip1 &= (k >= lastOne[i + p]);
                p ++;
            }
            if(num2 == 0 && noSkip1) {
                dp[i + j + 1][0] += dp[i][j];
                dp[i + j + 1][0] %= mod;
            }
        }
        ans += dp[i][n - i - 1];
        ans %= mod;
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n - i; j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    cout << ans << "\n";
    
    return 0;
}
