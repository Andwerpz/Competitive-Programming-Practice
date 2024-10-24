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

//Codeforces - 2022C

//annoying dp. 

bool a_win(char a, char b, char c) {
    int cnt = (a == 'A') + (b == 'A') + (c == 'A');
    return cnt >= 2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<string> a(2);
        cin >> a[0] >> a[1];
        vvi dp(n + 5, vi(2, 0));
        for(int i = 0; i < n; i++){
            if(i % 3 == 0){
                //flat
                dp[i + 3][0] = max(dp[i + 3][0], dp[i][0] + a_win(a[0][i], a[0][i + 1], a[0][i + 2]) + a_win(a[1][i], a[1][i + 1], a[1][i + 2]));
                dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + a_win(a[0][i], a[1][i], a[0][i + 1]));
                dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + a_win(a[0][i], a[1][i], a[1][i + 1]));
            }
            else if(i % 3 == 1){
                //top forwards
                dp[i + 2][0] = max(dp[i + 2][0], dp[i][0] + a_win(a[0][i + 1], a[1][i + 1], a[1][i]));
                dp[i + 3][0] = max(dp[i + 3][0], dp[i][0] + a_win(a[0][i + 1], a[0][i + 2], a[0][i + 3]) + a_win(a[1][i], a[1][i + 1], a[1][i + 2]));
                //bottom forwards
                dp[i + 2][0] = max(dp[i + 2][0], dp[i][1] + a_win(a[0][i + 1], a[1][i + 1], a[0][i]));
                dp[i + 3][1] = max(dp[i + 3][1], dp[i][1] + a_win(a[1][i + 1], a[1][i + 2], a[1][i + 3]) + a_win(a[0][i], a[0][i + 1], a[0][i + 2]));
            }
            else {
                continue;
            }
        }
        cout << dp[n][0] << "\n";
    }
    
    return 0;
}