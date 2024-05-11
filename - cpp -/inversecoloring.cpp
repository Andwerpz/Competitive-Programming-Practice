#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1027E

//notice that if we determine the color of the first row and the first column, we've determined the color
//of all the tiles on the board. 

//next, we count for each i from 1 to n, how many colorings of the first row will have at most i contiguous
//tiles of the same color. 

//then, for each value of i for the first row, we find the maximum j for the first column where j * i < k. 
//We can therefore match any coloring of rows that have maximum <= i with any column maximum <= j. 

//one thing to watch out for is that you can invert any coloring to produce another valid coloring. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    ll mod = 998244353;
    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0)));
    dp[0][1][1] = 1;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                //different
                dp[1][j][1] = (dp[1][j][1] + dp[0][j][k]) % mod;
                //same
                dp[1][max(j, k + 1)][k + 1] = (dp[1][max(j, k + 1)][k + 1] + dp[0][j][k]) % mod;
            }
        }
        swap(dp[0], dp[1]);
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                dp[1][j][k] = 0;
            }
        }
    }
    vector<ll> cnt(n + 1, 0);
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            cnt[i] += dp[0][i][j];
            cnt[i] %= mod;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; i * j < k && j <= n; j++){
            ans += cnt[i] * cnt[j];
            ans %= mod;
        }
    }
    ans *= 2;
    ans %= mod;
    cout << ans << "\n";
    
    return 0;
}
