#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1989E

//first, notice that the conversion from a->b is a red herring (in my opinion). We can instead figure out how many
//ways there are to directly construct b. 

//define a segment as a subarray in b that is generated by a subarray in a of the same value. a k-segment is 
//just a segment of length k. Naively, we can do dp across b where every index we can decide whether to continue or 
//terminate the current segment. The problem is that 1-segments and 2-segments look identical; they both only 
//consist of 1s, so our naive dp would overcount. 

//to fix this, we can also keep track of the size of our current segment, and whether or not we are currently
//making a one or non-one segment. 

//ok, imma stop here, my solution is very jank, and i don't want to explain it in it's entirety. The gist is 
//combinatorics using dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll mod = 998244353;
    int n, k;
    cin >> n >> k;
    //i
    //is one segment
    //current length of segment
    //number of total segments
    int maxl = 2;
    vector dp(n + 1, vector(2, vector(maxl + 1, vector<ll>(k + 1, 0))));
    dp[1][0][0][1] = 1;
    dp[1][1][0][1] = 1;
    for(int i = 1; i < n; i++){
        for(int j = 0; j <= k; j++){
            for(int l = 0; l <= maxl; l++){
                //is one segment
                {
                    //keep going
                    dp[i + 1][1][min(l + 1, maxl)][min(j + 1, k)] += dp[i][1][l][j];
                    dp[i + 1][1][min(l + 1, maxl)][min(j + 1, k)] %= mod;
                    //stop here, must go into non-one segment
                    dp[i + 1][0][0][min(j + 1, k)] += dp[i][1][l][j];
                    dp[i + 1][0][0][min(j + 1, k)] %= mod;
                }
                //is not one segment
                {
                    //keep going
                    dp[i + 1][0][min(l + 1, maxl)][j] += dp[i][0][l][j];
                    dp[i + 1][0][min(l + 1, maxl)][j] %= mod;
                    //stop here. l must be maximum
                    //orr, a length 2 segment is acceptable if i == 2
                    if(l == maxl || (l == maxl - 1 && i == 2)){
                        //go to one segment
                        dp[i + 1][1][0][min(j + 1, k)] += dp[i][0][l][j];
                        dp[i + 1][1][0][min(j + 1, k)] %= mod;
                        //go to non-one segment
                        dp[i + 1][0][0][min(j + 1, k)] += dp[i][0][l][j];
                        dp[i + 1][0][0][min(j + 1, k)] %= mod;
                    }
                }
            }
        }
    }
    // for(int i = 0; i <= n; i++){
    //     for(int j = 0; j <= k; j++){
    //         cout << "I K : " << i << " " << j << " : ";
    //         for(int l = 0; l <= maxl; l++){
    //             cout << dp[i][0][l][j] << " " << dp[i][1][l][j] << ", ";
    //         }
    //         cout << "\n";
    //     }
    // }
    ll ans = 0;
    //must have at least k segments
    //if is not one segment, segment length must be 2 or 3
    ans += dp[n][0][maxl][k];
    ans += dp[n][0][maxl - 1][k];
    for(int i = 0; i <= maxl; i++){
        ans += dp[n][1][i][k];
    }
    ans %= mod;
    cout << ans << "\n";
    
    return 0;
}