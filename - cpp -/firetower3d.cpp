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

//HammerWars 2025 - A1 A2

//for each cell, record the time at which it gets lit on fire
//then, it's just some simple math to figure out the final height of the fire column at each point. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m, k, d;
    cin >> n >> m >> k >> d;
    vvl g(n, vl(m, 1e18));
    queue<pii> q;
    for(int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        r --, c --;
        g[r][c] = 0;
        q.push({r, c});
    }
    vi dr = {-1, 1, 0, 0};
    vi dc = {0, 0, -1, 1};
    while(q.size() != 0) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(g[nr][nc] == 1e18) {
                g[nr][nc] = g[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(d - g[i][j] >= 0) ans += d - g[i][j] + 2;
    }
    ans -= k;
    cout << ans << "\n";
    
    return 0;
}