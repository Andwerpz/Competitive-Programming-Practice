#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//AtCoder - ABC265E

//a path consists of an array of the moves taken. A path 'a' is different from path 'b' if in one location,
//the move taken differs. Where they end up doesn't matter. 

//we can do a 3 state dp, dp[i][j][k] is the number of paths to move (a, b) i times, (c, d) j times, and 
//(e, f) k times. 

//the answer is simply the sum of dp[i][j][k] where i + j + k == n. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    ll a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    set<pair<ll, ll>> s;
    for(int i = 0; i < m; i++){
        pair<ll, ll> next;
        cin >> next.first >> next.second;
        s.insert(next);
    }
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0)));\
    dp[0][0][0] = 1;
    ll mod = 998244353;
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                ll x = a * (ll) i + c * (ll) j + e * (ll) k;
                ll y = b * (ll) i + d * (ll) j + f * (ll) k;
                if(s.find({x, y}) != s.end()){
                    continue;
                }
                if(i != 0){
                    dp[i][j][k] += dp[i - 1][j][k];
                }
                if(j != 0){
                    dp[i][j][k] += dp[i][j - 1][k];
                }
                if(k != 0){
                    dp[i][j][k] += dp[i][j][k - 1];
                }
                while(dp[i][j][k] >= mod){
                    dp[i][j][k] -= mod;
                }
                if(i + j + k == n){
                    ans += dp[i][j][k];
                    if(ans >= mod){
                        ans -= mod;
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
