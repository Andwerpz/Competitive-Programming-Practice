#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

ll mod = 1e9 + 7;
int x;
ll solve(int sum, vector<int>& c, vector<ll>& dp){
    if(sum > x) {
        return 0;
    }
    if(sum == x){
        return 1;
    }
    if(dp[sum] != -1){
        return dp[sum];
    }
    dp[sum] = 0;
    for(int i = 0; i < c.size(); i++){
        dp[sum] += solve(sum + c[i], c, dp);
        dp[sum] %= mod;
    }
    return dp[sum];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n >> x;
    vector<int> c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    vector<ll> dp(x + 1, -1);
    //dp[i] = number of ways to get from sum i -> x
    cout << solve(0, c, dp) << "\n";
    
    return 0;
}
