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

// BAPC 2023 - J

//first, root the tree arbitrarily. Then if we want to compute the number of connected subtrees of exactly K
//nodes, we can compute for each node, the number of connected subtrees of K nodes that are rooted at that node. 

//observe that this can be done by first computing the counts for all of a nodes children, and then convolving them
//to get the answer for the root. And since N = 1000, this is fast enough for some reason. Technically, the
//complexity is O(n^3), but alot of the time we don't do that much computation at each edge. 

const ll mod = 1e9 + 7;
const int N = 1001;
ll dp[N][N];
ll tmp[N];
int sz[N];
vvi c;
int n;

void dfs(int cur) {
    sz[cur] = 1;
    for(int x : c[cur]) {
        dfs(x);
        sz[cur] += sz[x];
    }
}

void solve(int cur) {
    dp[cur][1] = 1;
    for(int x : c[cur]) {
        solve(x);
        for(int i = 0; i <= sz[cur]; i++) tmp[i] = 0;
        for(int i = 1; i <= sz[cur]; i++) {
            for(int j = 1; j <= i; j++) {
                tmp[i] += (dp[cur][j] * dp[x][i - j]) % mod;
                if(tmp[i] >= mod) tmp[i] -= mod;
            }
        }
        for(int i = 0; i <= sz[cur]; i++) dp[cur][i] = tmp[i];
    }
    dp[cur][0] = 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    c = vvi(n);
    for(int i = 1; i < n; i++) {
        int p;
        cin >> p;
        c[p].push_back(i);
    }
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) {
        dp[i][j] = 0;
    }
    dfs(0);
    solve(0);
    for(int i = 1; i <= n; i++) {
        ll ans = 0;
        for(int j = 0; j < n; j++) ans += dp[j][i];
        ans %= mod;
        cout << ans << "\n";
    }

    // cout << "DP : \n";
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j <= n; j++) cout << dp[i][j] << " ";
    //     cout << "\n";
    // }
    
    return 0;
}