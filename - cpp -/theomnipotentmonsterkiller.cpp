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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1988D

//first, root the tree arbitrarily. Next, observe that we can probably do a dp solution: dp[i][j] = minimum cost of
//subtree rooted at node i given that we kill i on the jth turn. 

//Computing dp[i][j] isn't too bad. We just have to keep in mind that if the current node is getting killed at turn
//j, then none of the children can be killed at turn j. 

//now the difficult part is setting the bounds for j. Of course, we can set the bounds for j from 1 to n, but that 
//will TLE. But if we set it too low, we might miss an optimal answer. Observe that if we have a solution, as in
//we know for each node when it's going to die, then the turn of a node should be equal to the MEX of all of 
//it's neighbors. This actually puts a bound of log(n) on j, which will not TLE. 

ll solve(int cur, int p, vvi& c, vvl& dp, int nr_alive, vl& a) {
    if(dp[cur][nr_alive] != -1){
        return dp[cur][nr_alive];
    }
    ll ans = a[cur] * (nr_alive + 1);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        ll cmin = 9e18;
        for(int j = 0; j < 20; j++){
            if(j == nr_alive){
                continue;
            }
            cmin = min(cmin, solve(next, cur, c, dp, j, a));
        }
        ans += cmin;
    }
    dp[cur][nr_alive] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vvi c(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        vvl dp(n, vl(20, -1));
        ll ans = 9e18;
        for(int i = 0; i < 20; i++){
            ans = min(ans, solve(0, -1, c, dp, i, a));
        }
        cout << ans << "\n";
    }
    
    return 0;
}