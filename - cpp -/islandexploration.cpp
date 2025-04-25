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

//University of Alberta Programming Contest 2025 Open - F

//floodfill

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    pii s;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'S') {
                s = {i, j};
                g[i][j] = '.';
            }
        }
    }
    int ans = 0;
    queue<pii> q;
    q.push(s);
    vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int r = q.front().first, c = q.front().second;
        q.pop();
        ans ++;
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i], nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(g[nr][nc] != '#') continue;
            g[nr][nc] = '.';
            q.push({nr, nc});
        }
    }
    cout << ans << "\n";
    
    return 0;
}