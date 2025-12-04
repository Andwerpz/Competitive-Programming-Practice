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

// UTPC 10-1-25 Div1 - A

//just check all spots

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> g[i][j];
    vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        int cans = g[i][j];
        for(int k = 0; k < 4; k++) {
            int nr = i + dr[k];
            int nc = j + dc[k];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            cans += g[nr][nc];
        }
        ans = max(ans, cans);
    }
    cout << ans << "\n";
    
    return 0;
}