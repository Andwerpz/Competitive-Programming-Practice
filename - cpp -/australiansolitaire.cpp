#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 01-26-24 Div.2 - H

//standard 3D dp. 
//i : how many cards we've placed
//j : number of aces used
//k : last card rank

//answer is i = n, any j k. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll mod = 1e9 + 7;
    //i : how many cards we've placed
    //j : number of aces used
    //k : last card rank
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(5, vector<ll>(13, 0)));
    dp[0][0][0] = 1;
    for(int i = 0; i < n; i++){
        for(int k = 0; k < 13; k++){
            for(int j = 0; j < 5; j++){
                //place some higher card than this one
                for(int l = k + 1; l < 13; l++){
                    dp[i + 1][j][l] += dp[i][j][k];
                    dp[i + 1][j][l] %= mod;
                }
                //place an ace
                if(j != 4) {
                    dp[i + 1][j + 1][0] += dp[i][j][k];
                    dp[i + 1][j + 1][0] %= mod;
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 13; j++){
            ans = (ans + dp[n][i][j]) % mod;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
