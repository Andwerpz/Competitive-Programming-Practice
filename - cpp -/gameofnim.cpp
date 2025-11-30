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

//UIUC IPL Team Tryout 2025 - E

//can do dp, dp[i][j][k] = number of ways given
// i = how many stones remaining
// j = max pile we can create as of now
// k = target xor

//goal state is dp[0][j][0]

//while this dp may seem infeasible, the observation is that not many states are actually reachable, so
//probably a recursive solution can work. 

ll mod;
ll dp[501][501][512];

ll calc(int rem, int mx, int x) {
    if(rem == 0) {
        if(x == 0) return 1;
        return 0;
    }
    if(dp[rem][mx][x] != -1) return dp[rem][mx][x];
    ll ans = 0;
    for(int i = 1; i <= min(rem, mx); i++) {
        ans += calc(rem - i, i, x ^ i);
        if(ans >= mod) ans -= mod;
    }
    dp[rem][mx][x] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, p;
    cin >> n >> p >> mod;
    for(int i = 0; i < 501; i++) for(int j = 0; j < 501; j++) for(int k = 0; k < 512; k++) dp[i][j][k] = -1;
    cout << calc(n - p, n - p, p) << "\n";
    
    return 0;
}