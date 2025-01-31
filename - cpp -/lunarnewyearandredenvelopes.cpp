#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1106E

//relatively straightforwards simulation using dp

//First observe that bob's actions can be completely determined from the current time. This is because 
//when he takes an envelope, it locks him out of all actions until after the window for taking the current 
//envelope is over. This means that he can never chose to take envelopes that he has already taken before, 
//so the only envelopes that he can choose to take are ones that he has never taken before. 

//We can probably use a dp solution. dp[i][j] = minimum number of coins given that we're at time i and we've
//bothered bob j times. 

//transitions are straightforwards. from dp[i][j] we can do
// - don't do anything. 
//   - if there is an envelope here, bob will take the best one
//   - otherwise, dp[i][j] -> dp[i + 1][j]
// - bother bob, dp[i][j] -> dp[i + 1][j + 1]

//we can precompute for all i which envelope is the best for bob to take using a frequency map. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pll>> s(n + 1), t(n + 1);
    for(int i = 0; i < k; i++){
        int l, r, d, w;
        cin >> l >> r >> d >> w;
        l --;
        s[l].push_back({w, d});
        t[r].push_back({w, d});
    }
    map<pll, int> f;
    vector<pll> a(n, {-1, -1});
    for(int i = 0; i < n; i++){
        for(pll x : s[i]) f[x] ++;
        for(pll x : t[i]) {
            f[x] --;
            if(f[x] == 0) f.erase(x);
        }
        if(f.size() != 0) a[i] = f.rbegin()->first;
    }
    vvl dp(n + 1, vl(m + 1, 1e18));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m; j++){
            //don't disturb
            if(a[i][0] != -1) dp[a[i][1]][j] = min(dp[a[i][1]][j], dp[i][j] + a[i][0]);
            else dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            //disturb
            if(j != m) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
        }
    }
    ll ans = 1e18;
    for(int i = 0; i <= m; i++) ans = min(ans, dp[n][i]);
    cout << ans << "\n";
    
    return 0;
}