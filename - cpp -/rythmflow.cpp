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

//2024 ICPC NAQ - K

//dp

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<ll> e(n+1), a(m+1);

    for (int i = 1; i <= n; ++i) {
        cin >> e[i];
    }

    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // can we match these?
            dp[i][j] = max({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            if (abs(e[i] - a[j]) > 102)
                continue;
            
            int points = 0;
            int diff = abs(e[i] - a[j]);

            if (diff <= 15) {
                points = 7;
            } else if (diff <= 23) {
                points = 6;
            } else if (diff <= 43) {
                points = 4;
            } else {
                points = 2;
            }

            dp[i][j] = max(dp[i][j], points + dp[i-1][j-1]);
        }
    }

    cout << dp[n][m] << endl;
    
    return 0;
}