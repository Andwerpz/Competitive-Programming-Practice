#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1369D

//any rooted tree >= level 3 can be described recursively; a level n tree has 1 level n - 1 child, and 2 level n - 2 children.

//Naturally, if we solve for the maximum answer on level n - 1 and n - 2 trees, then we can easily solve for the answer on
//a level n tree. 

//The only point of conflict when it comes to picking claws is whether or not the root is already colored yellow. So define
//dp[i][j] = maximum number of claws picked on level i tree where
//j = 1 if root is colored yellow and j = 0 if otherwise. 

//dp transitions are pretty obvious. Check implementation if confused. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll mod = 1e9 + 7;
    vector<vector<ll>> dp(2e6 + 100, vector<ll>(2, 0));
    dp[3][1] = 1;
    for(int i = 4; i < dp.size(); i++){
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + max(dp[i - 2][0], dp[i - 2][1]) * 2;
        dp[i][0] %= mod;
        dp[i][1] = dp[i - 1][0] + dp[i - 2][0] * 2 + 1;
        dp[i][1] %= mod;
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        cout << (max(dp[n][0], dp[n][1]) * 4) % mod << "\n";
    }
    
    return 0;
}