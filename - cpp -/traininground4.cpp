#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// typedef vector<ll> vi;
// typedef pair<ll, ll> pii;

// ICPC PACNW 2025 - L

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n; cin >> n;
    vector<array<ll,2>> a(n);
    ll m1 = 0, m2 = 0;
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
        m1 = max(m1, x[0]);
        m2 = max(m2, x[1]);
    }

    m1 -= 55;
    m2 -= 55;

    for(auto &x : a) {
        x[0] -= m1;
        x[1] -= m2;
    }

    vector dp(n + 1, vector(200, vector<ll>(200 , INT_MAX)));
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 200; j++) {
            dp[0][i][j] = i + j;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 200; j++) {
            for(int k = 0; k < 200; k++) {
                if(j >= a[i][0] && k >= a[i][1]) {
                    if(j + 1 < 200) {
                        dp[i+1][j+1][k] = min(dp[i+1][j+1][k], dp[i][j][k]);
                    }
                    if(k + 1 < 200) {
                        dp[i+1][j][k+1] = min(dp[i+1][j][k+1], dp[i][j][k]);
                    }
                }
            }
        }
    }

    ll res = INT_MAX;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 200; j++) {
            res = min(res, dp[n][i][j]);
        }
    }

    cout << res + m1 + m2 << '\n';

    return 0;
}