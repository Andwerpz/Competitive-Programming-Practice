#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1699D

//we can fully remove all the elements in a given subarray [i, j] if the number of elements is even, and
//there is not an element which makes up the majority of the subarray (more than 50%). 
//Since n <= 5000, we can just precompute for any subarray, whether or not we can remove it. 

//now, let's try to solve the problem. For a given value x, we can use dp to find out the maximum size array
//we can reduce to with only x's: dp[i] = maximum number of x's we can extract from the prefix [0, i). 
//for every dp[i], if a[i] == x, then we can take that x, and move to dp[i + 1], leading to transition
//dp[i + 1] := dp[i] + 1. 

//we can also just remove some subarray that is ahead of us, leading to transition
//dp[i + k] := dp[i] for all k where i + k <= n, and we can remove the subarray [i, k]

//one problem is that since transitions are O(n), testing some value x costs O(n^2), and testing all values of
//x will cost O(n^3). To get around this, we can observe that the only values of dp[i] that matter are when 
//a[i] == x, and i == 0 (for the base case). This means that testing all values of x is actually only O(n^2), as
//only around O(n) dp values actually matter. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        //precompute ranges
        //can_rem[i][j] = true if we can fully reduce the range [i, j]
        vector<vector<bool>> can_rem(n, vector<bool>(n, false));    
        for(int i = 0; i < n; i++){
            int tot = 0;
            vector<int> fm(n, 0);
            int mx = 0;
            for(int j = i; j < n; j++){
                fm[a[j]] ++;
                mx = max(mx, fm[a[j]]);
                tot ++;
                if(tot % 2 == 0 &&  mx * 2 <= tot) {
                    can_rem[i][j] = true;
                }
            }
        }
        //do dp
        //dp[i][j] = for the ith prefix, what's the maximum amount of consecutive j's we can make?
        vector<vector<int>> dp(n + 1, vector<int>(n, -1));
        //base case
        for(int i = 0; i < n; i++){
            dp[0][i] = 0;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dp[i][j] == -1){
                    continue;
                }
                //take the current value
                if(a[i] == j) {
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + 1);
                }
                //skip some values
                for(int k = i; k < n; k++){
                    if(can_rem[i][k] && (k + 1 == n || a[k + 1] == j)) {
                        dp[k + 1][j] = max(dp[k + 1][j], dp[i][j]);
                    }
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            ans = max(ans, dp[n][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}