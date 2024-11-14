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

//Alberta Collegiate Programming Contest 2024, Open Division - E

//can just do dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvl a(n, vl(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    vvl dp(n, vl(m, -1e18));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(dp[i][j] < 0){
                continue;
            }
            if(i != n - 1){
                ll ns = dp[i][j] + a[i][j] - a[i + 1][j] - 10;
                if(ns >= 0){
                    dp[i + 1][j] = max(dp[i + 1][j], ns);
                }
            }
            if(j != m - 1){
                ll ns = dp[i][j] + a[i][j] - a[i][j + 1] - 10;
                if(ns >= 0){
                    dp[i][j + 1] = max(dp[i][j + 1], ns);
                }
            }
            if(i != n - 1 && j != m - 1){
                ll ns = dp[i][j] + a[i][j] - a[i + 1][j + 1] - 15;
                if(ns >= 0){
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], ns);
                }
            }
        }
    }
    if(dp[n - 1][m - 1] == -1e18){
        cout << "TOO SLOW\n";
    }
    else {
        cout << dp[n - 1][m - 1] << "\n";
    }
    
    return 0;
}