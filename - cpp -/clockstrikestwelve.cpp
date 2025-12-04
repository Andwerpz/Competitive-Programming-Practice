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

//UTPC 11-12-2025 Div1 - D

//this is just dp,
//dp[i][j] = minimum number of coins used given
// i = current value sum
// j = current time sum

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;
    vi W(N);
    for(int i = 0; i < N; i++) cin >> W[i];
    vi T(N);
    for(int i = 0; i < N; i++) cin >> T[i];
    vvi dp(M + 1, vi(K + 1, 1e9));  //value, time
    dp[0][0] = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= M; j++) {
            for(int k = 0; k <= K; k++) {
                //use coin here
                if(k + T[i] <= K && j + W[i] <= M) {
                    dp[j + W[i]][k + T[i]] = min(dp[j + W[i]][k + T[i]], dp[j][k] + 1);
                }
            }
        }
    }
    int ans = 1e9;
    for(int i = 0; i <= K; i++) ans = min(ans, dp[M][i]);
    if(ans == 1e9) cout << "-1\n";
    else cout << ans << "\n";
    
    return 0;
}