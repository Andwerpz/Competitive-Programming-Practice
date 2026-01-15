#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - I

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll na, nb, mod; cin >> na >> nb >> mod;

    vector<vector<ll>> dp(na + 1, vector<ll> (nb + 1));
    dp[1][1] = 1;
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * (i + j - 1)) % mod;
            dp[i][j] = (dp[i][j] + dp[i][j - 1] * (i + j - 1)) % mod;
            dp[i][j] = (dp[i][j] - dp[i - 1][j - 1] * (i + j - 2) % mod * (i + j - 2)) % mod;
        }
    }

    cout << (dp[na][nb] % mod + mod) % mod << '\n';

    return 0;
}