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

//CSES - 1112

//not really a string problem, more PIE

//dp[i][j][k] = number of ways given
//i = nr letters considered (kinda)
//j = how many patterns guaranteed
//k = distance to last time you placed a pattern 
//can only set arbitrary letters when k == m, otherwise next letter is fixed

const ll mod = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = s.size();
    vb okd(m + 1, true);
    for(int i = 0; i <= m; i++){
        for(int j = 0; i + j < m; j++){
            if(s[j] != s[i + j]) {
                okd[i] = false;
            }
        }
    }
    vector<vvl> dp(2, vvl(n + 1, vl(m + 1, 0)));
    dp[0][0][m] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 1; k <= m; k++){
                dp[1][j][k] = 0;
            }
        }
        for(int j = 0; j <= n; j++){
            for(int k = 1; k <= m; k++){
                if(k == m){
                    //place arbitrary character
                    dp[1][j][m] += (dp[0][j][m] * 26);
                    dp[1][j][m] %= mod;
                    //place pattern
                    if(j != n && i + m <= n){
                        dp[1][j + 1][1] += dp[0][j][m];
                        dp[1][j + 1][1] %= mod;
                    }
                }
                else {
                    //place next character of pattern
                    dp[1][j][k + 1] += dp[0][j][k];
                    dp[1][j][k + 1] %= mod;
                    //place pattern
                    if(j != n && i + m <= n && okd[k]) {
                        dp[1][j + 1][1] += dp[0][j][k];
                        dp[1][j + 1][1] %= mod;
                    }
                }
            }
        }
        swap(dp[0], dp[1]);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ans += dp[0][i][m] * (i % 2 == 1? 1 : -1);
        ans = (ans + mod) % mod;
    }
    cout << ans << "\n";
    
    return 0;
}