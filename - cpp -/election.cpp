#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 B

void solve() {
     
    int n; cin >> n;

    int v1, v2; cin >> v1 >> v2;
    int w; cin >> w;


    int rem = n - v1 - v2;

    int need = (n) / 2 + 1;

    // cerr << "need : " << need << endl;

    if ((v1 + rem) < need) {
        cout << "RECOUNT!" << endl;
        return;
    }

    vector<vector<ll>> dp(rem+1, vector<ll>(rem+1));

    dp[0][0] = 1;

    for (int i = 1; i <= rem; ++i) {
        for (int j = 0; j <= rem; ++j) {
            if (j != 0) {
                dp[i][j] += dp[i-1][j-1];
            }
            dp[i][j] += dp[i-1][j];
            // cerr << dp[i][j] << " ";
        }
        // cerr << endl;
    }

    // for (auto v : dp) {
        // for (auto x)
    // }

    // if (v1 >= need) {
    //     cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << endl;
    //     return;
    // }


    ll wins = 0;

    int winning = need - v1;
    winning = max(winning, 0);
    // cerr << "winning : " << winning << endl;

    for (int i = winning; i <= rem; ++i) {
        wins += dp[rem][i];
    }

    // cerr << "wins : " << wins << endl;

    ll two = 1;
    for (int i = 0; i < rem; ++i) two = two * 2;

    ld prob = (ld) wins / (ld)two;

    // cerr << "prob : " << prob << endl;

    if ((prob * 100) > w) {
        cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << endl;
    } else cout << "PATIENCE, EVERYONE!" << endl;


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
   int tc; cin >> tc;
   while (tc--) {
    solve();
   }
    
    
    return 0;
}
