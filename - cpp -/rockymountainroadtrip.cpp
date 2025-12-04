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

//Mines HSPC 2025 Open Division - M

//bfs, keep track of whether or not you gained elevation on the last move. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi h(n, vi(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> h[i][j];
    int r0, c0, r1, c1;
    cin >> r0 >> c0 >> r1 >> c1;
    r0 --, c0 --, r1 --, c1 --;
    vector<vvi> d(2, vvi(n, vi(m, 1e9)));
    d[0][r0][c0] = 0, d[1][r0][c0] = 0;
    queue<pair<int, pii>> q;
    q.push({0, {r0, c0}});
    q.push({1, {r0, c0}});
    vi dr = {-1, -1, -1, 0, 0, 1, 1, 1}, dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    while(q.size() != 0){
        int linc = q.front().first;
        int r = q.front().second.first, c = q.front().second.second;
        q.pop();
        // cout << "CUR : " << linc << " " << r << " " << c << "\n";
        for(int i = 0; i < 8; i++){
            int nr = r + dr[i], nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(h[r][c] == h[nr][nc]) continue;
            int cinc = h[nr][nc] > h[r][c];
            if(linc == cinc) continue;
            if(d[cinc][nr][nc] != 1e9) continue;
            d[cinc][nr][nc] = d[linc][r][c] + 1;
            q.push({cinc, {nr, nc}});
        }
    }
    int ans = min(d[0][r1][c1], d[1][r1][c1]);
    if(ans == 1e9) cout << "-1\n";
    else cout << ans << "\n";
    
    return 0;
}