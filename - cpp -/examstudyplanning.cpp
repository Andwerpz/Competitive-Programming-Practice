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

// BAPC 2023 - E

//dp[i][j] = maximum spare time given
// we're on the ith exam
// we've passed j exams

//at any state, we can either choose to prepare for the current exam, or don't prepare. 
//note that we can only prepare if dp[i][j] >= a[i]

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl s(n + 1), p(n), e(n), a(n);
    for(int i = 0; i < n; i++) cin >> s[i] >> p[i] >> e[i] >> a[i];
    s[n] = 2e9;
    vvl dp(n + 1, vl(n + 1, -1));   
    dp[0][0] = s[0];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dp[i][j] == -1) continue;
            //don't prepare for this one
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + (s[i + 1] - e[i]));
            //prepare for this one
            if(dp[i][j] >= a[i]) {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] - a[i] + (s[i + 1] - p[i]));
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++) if(dp[n][i] != -1) ans = i;
    cout << ans << "\n";
    
    return 0;
}