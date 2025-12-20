#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

//ICPC ECNA 2025 - K

ll dp[52][53][53][53][3][2];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // cout << 52 * 53 * 53 * 53 * 3 * 2 << '\n';

    ll w, d; cin >> w >> d;

    // dp[index][acnt][bcnt][ccnt][prev][prevcnt]
    // vector dp(w, vector(w + 1, vector(w + 1, vector(w + 1, vector(3, vector<ll>(2))))));

    dp[0][1][0][0][0][0] = 1;
    dp[0][0][1][0][1][0] = 1;
    dp[0][0][0][1][2][0] = 1;

    ll res = 0;

    auto sub = [&](int i, int j, int k, ll val) -> void {
        // cout << "sub : " << val << '\n';
        if(max({abs(i-j),abs(i-k),abs(j-k)}) <= d) {
            res -= val;
        }
    };

    for(int i = 0; i + 1 < w; i++) {
        for(int j = 0; j < w; j++) {
            for(int k = 0; k < w; k++) {
                for(int l = 0; l < w; l++) {
                    //transition from a to b and c
                    dp[i+1][j][k+1][l][1][0] += dp[i][j][k][l][0][0];
                    dp[i+1][j][k][l+1][2][0] += dp[i][j][k][l][0][0];

                    //transition from b0 to all 3
                    dp[i+1][j+1][k][l][0][0] += dp[i][j][k][l][1][0];
                    dp[i+1][j][k+1][l][1][1] += dp[i][j][k][l][1][0];
                    dp[i+1][j][k][l+1][2][0] += dp[i][j][k][l][1][0];

                    //transition from b1 to a and c
                    dp[i+1][j+1][k][l][0][0] += dp[i][j][k][l][1][1];
                    dp[i+1][j][k][l+1][2][0] += dp[i][j][k][l][1][1];

                    //transition from c to a and b
                    dp[i+1][j+1][k][l][0][0] += dp[i][j][k][l][2][0];
                    dp[i+1][j][k+1][l][1][0] += dp[i][j][k][l][2][0];

                    if(w % 2 == 1 && i == w / 2 - 1) {
                        //ab
                        sub(j * 2, k * 2 + 1, l * 2, dp[i][j][k][l][0][0]);
                        //ac
                        sub(j * 2, k * 2, l * 2 + 1, dp[i][j][k][l][0][0]);

                        //ba
                        sub(j * 2 + 1, k * 2, l * 2, dp[i][j][k][l][1][0]);
                        //bc
                        sub(j * 2, k * 2, l * 2 + 1, dp[i][j][k][l][1][0]);

                        //bba
                        sub(j * 2 + 1, k * 2, l * 2, dp[i][j][k][l][1][1]);
                        //bbc
                        sub(j * 2, k * 2, l * 2 + 1, dp[i][j][k][l][1][1]);

                        //ca
                        sub(j * 2 + 1, k * 2, l * 2, dp[i][j][k][l][2][0]);
                        //cb
                        sub(j * 2, k * 2 + 1, l * 2, dp[i][j][k][l][2][0]);
                    }

                    if(w % 2 == 0 && i == w / 2 - 1) {
                        //bb
                        sub(j * 2, k * 2, l * 2, dp[i][j][k][l][1][0]);
                    }
                }
            }
        }
    }

    // cout << "642364119295016204" << " max : " << LLONG_MAX << "\n";

    // cout << "div : " << LLONG_MAX / 642364119295016204LL << '\n';

    // cout << dp[2][1][1][1][0][0] << '\n';
    // cout << dp[2][1][1][1][1][0] << '\n';
    // cout << dp[2][1][1][1][2][0] << '\n';

    for(int i = 0; i <= w; i++) {
        for(int j = 0; j <= w; j++) {
            for(int k = 0; k <= w; k++) {
                for(int l = 0; l < 3; l++) {
                    for(int m = 0; m < 2; m++) {
                        if(max({abs(i - j),abs(i-k),abs(j - k)}) <= d) {
                            res += dp[w - 1][i][j][k][l][m];

                        }
                    }
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}