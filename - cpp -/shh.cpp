#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - K

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, K; cin >> n >> K;
    string s; cin >> s;

    vector dp(n + 1, vector(n + 1, vector(K + 1, vector<array<int,2>>(3, {0, 0}))));

    auto get_next_kl = [&](int k, int l, char c) -> array<int,2> {
        if(l == 2 && c == 'h') k++;

        int resl;

        if(l == 0) {
            if(c == 's') {
                resl = 1;
            } else {
                resl = 0;
            }
        } else if(l == 1) {
            if(c == 'h') {
                resl = 2;
            } else if(c == 's') {
                resl = 1;
            } else {
                resl = 0;
            }
        } else if(l == 2) {
            if(c == 's') {
                resl = 1;
            } else {
                resl = 0;
            }
        }

        return {k, resl};

    };

    dp[0][0][0][0] = {1,1};

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k <= K; k++) {
                for(int l = 0; l < 3; l++) {
                    if(dp[i][j][k][l][0]) {
                        //try no operation
                        {
                            int ni = i + 1;
                            int nj = j;
                            auto [nk, nl] = get_next_kl(k, l, s[i]);
                            assert(ni <= n && nj <= n);
                            if(nk <= K) {
                                dp[ni][nj][nk][nl][0] = 1;
                                dp[ni][nj][nk][nl][1] = (dp[ni][nj][nk][nl][1] + dp[i][j][k][l][1]) % 67;
                            }
                        }
                        //try doing operation
                        for(char c = 'a'; c <= 'z'; c++) {
                            int ni = i + 1;
                            int nj = j + 1;
                            auto [nk, nl] = get_next_kl(k, l, c);
                            assert(ni <= n && nj <= n);
                            if(nk <= K) {
                                dp[ni][nj][nk][nl][0] = 1;
                                dp[ni][nj][nk][nl][1] = (dp[ni][nj][nk][nl][1] + dp[i][j][k][l][1]) % 67;
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "dp val 1 : " << dp[2][2][0][2][1] << endl;

    // cout << "dp val 2 : " << dp[5][3][1][0][1] << endl;

    // cout << "dp val 3 : " << dp[7][3][1][1][1] << endl;

    // cout << "mih5" << endl;

    // vector dp(n + 1, vector(n + 1, vector(K + 1, vector<array<int,2>>(3, {0, 0}))));

    int mo = INT_MAX;
    for(int i = 0; i <= n; i++) {
        int j = K;
        for(int k = 0; k < 3; k++) {
            if(dp[n][i][j][k][0]) mo = min(mo, i);
        }
    }

    // cout << "mo: " << mo << endl;

    // cout << "mih6" << endl;

    int res = 0;
    int i = mo;
    int j = K;
    for(int k = 0; k < 3; k++) {
        // cout << "k : " << k << " val : " << dp[n][i][j][k][1] << endl;;
        res += dp[n][i][j][k][1];
    }

    // cout << "mih7" << endl;

    cout << mo << " " << res % 67 << '\n';

    return 0;
}