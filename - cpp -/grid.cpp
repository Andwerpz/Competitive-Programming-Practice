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

//Kattis - grid

//bfs on grid

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    vvi d(n, vi(m, 1e9));
    queue<pii> q;
    q.push({0, 0});
    d[0][0] = 0;
    vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int r = q.front().first, c = q.front().second;
        q.pop();
        // cout << "R C : " << r << " " << c << "\n";
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i] * (g[r][c] - '0'), nc = c + dc[i] * (g[r][c] - '0');
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            int ndist = d[r][c] + 1;
            if(ndist < d[nr][nc]) {
                d[nr][nc] = ndist;
                q.push({nr, nc});
            }
        }
    }
    cout << (d[n - 1][m - 1] == 1e9? -1 : d[n - 1][m - 1]) << "\n";
    
    return 0;
}