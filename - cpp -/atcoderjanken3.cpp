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

//AtCoder - ABC365D

//dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vvi dp(n + 1, vi(3, -1e9));
    dp[0] = {0, 0, 0};
    for(int i = 1; i <= n; i++){
        //choose rock
        if(s[i - 1] != 'P') {
            dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + (s[i - 1] == 'S');
        }
        //choose paper
        if(s[i - 1] != 'S') {
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + (s[i - 1] == 'R');
        }
        //choose scissors
        if(s[i - 1] != 'R') {
            dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + (s[i - 1] == 'P');
        }
    }
    cout << max({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
    
    return 0;
}