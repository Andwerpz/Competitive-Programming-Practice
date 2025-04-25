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

//Codeforces - 2096C

//observe that the rows and columns are independent. 

//suppose we want to solve the rows. We can just do dp on the rows where dp[i][j] = min amount of money spent 
//so far given that we're on the ith row and j = last row was incremented?

ll solve(vvi& h, vl& a) {
    // cout << "SOLVE" << endl;
    int n = a.size();
    vvl dp(n + 1, vl(2, 1e18));
    dp[1][0] = 0, dp[1][1] = a[0];
    for(int i = 1; i < n; i++){
        // cout << "I : " << i << endl;
        for(int j = 0; j < 2; j++){
            // cout << "J : " << j << endl;
            bool p0v = true, p1v = true;
            for(int k = 0; k < n; k++){
                if(h[i][k] == h[i - 1][k] + j) p0v = false;
                if(h[i][k] + 1 == h[i - 1][k] + j) p1v = false;
            }
            if(p0v) dp[i + 1][0] = min(dp[i + 1][0], dp[i][j]);
            if(p1v) dp[i + 1][1] = min(dp[i + 1][1], dp[i][j] + a[i]);
        }
    }
    return min(dp[n][0], dp[n][1]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vvi h(n, vi(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) cin >> h[i][j];
        }
        vl a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        ll ans = solve(h, a);
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++) swap(h[i][j], h[j][i]);
        }
        ans += solve(h, b);
        if(ans >= 1e18) ans = -1;
        cout << ans << "\n";
    }
    
    return 0;
}