#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//2025 ICPC Asia Pacific Championship - J

//range dp. dp[l][r] = cost of merging groups l to r into position l. 
//fixing r, we can compute dp[l][r] for all l < r in O(n^2) time. This can be done using another dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi p(n);
    for(int i = 0; i < n; i++) cin >> p[i];
    vi ppos(n);
    for(int i = 0; i < n; i++) p[i] -= 1, ppos[p[i]] = i;
    //cost of merging groups [l, r], includes cost for moving group r to l
    vvi dp(n + 1, vi(n + 1, 1e9));
    dp[0][0] = 0;
    for(int i = 1; i < n; i++){
        // cout << "I : " << i << "\n";
        //from the ith group, 
        //min cost to merge [j, i] into i, excluding the cost of [j, k - 1]
        vvi idp(i, vi(i + 1, 1e9));
        idp[i - 1][i] = 0;
        for(int j = i - 1; j > 0; j--){
            for(int k = i; k > 0; k--){
                if(idp[j][k] == 1e9) continue;
                //continue segment
                idp[j - 1][k] = min(idp[j - 1][k], idp[j][k]);
                //start new segment
                idp[j - 1][j] = min(idp[j - 1][j], idp[j][k] + dp[j][k - 1] + abs(ppos[j] - ppos[k]));
            }
        }
        //include cost of [j, k]
        for(int j = i - 1; j >= 0; j--){
            for(int k = i; k > 0; k--){
                if(idp[j][k] == 1e9) continue;
                idp[j][k] += dp[j][k - 1] + abs(ppos[j] - ppos[k]);
                // cout << idp[j][k] << " ";
            }
            // cout << "\n";
        }
        //update dp
        dp[i][i] = 0;
        for(int j = 0; j < i; j++){
            for(int k = j + 1; k <= i; k++){
                dp[j][i] = min(dp[j][i], idp[j][k]);
            }
        }
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = i; j >= 0; j--) {
    //         cout << "DP : " << i << " " << j << " " << dp[j][i] << "\n";
    //     }
    // }
    cout << dp[0][n - 1] << "\n";
    
    return 0;
}