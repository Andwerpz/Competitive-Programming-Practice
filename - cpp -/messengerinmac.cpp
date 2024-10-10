#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1935C

//dp[i][j] = min time sum where
//i = number of messages in set
//j = we've taken the jth message

//naively, this solution is n^3, but we can notice that dp[i][j] only depends on the minimum value
//in the prefix of dp[i - 1], so we can optimize it down to n^2. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, l;
        cin >> n >> l;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        sort(a.begin(), a.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
            return a.second < b.second;
        });
        vector<vector<int>> dp(n + 1, vector<int>(n, l + 1));
        //base cases
        for(int i = 0; i < n; i++){
            dp[1][i] = min(dp[1][i], a[i].first);
        }
        for(int i = 2; i <= n; i++){
            int min_prev = l + 1;
            for(int j = 0; j < n; j++){
                dp[i][j] = min(dp[i][j], min_prev + a[j].first);
                if(j != n - 1){
                    min_prev = min(min_prev, dp[i - 1][j]);
                    min_prev = min(min_prev + a[j + 1].second - a[j].second, l + 1);
                }
            }
        }
        int ans = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < n; j++){
                if(dp[i][j] <= l){
                    ans = i;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
