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

//2025 NAQ - D

//do BFS on the maze, but also keep track of what direction you're currently facing as 
//part of the state. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int sr, sc, er, ec;
    cin >> sr >> sc >> er >> ec;
    sr --, sc --, er --, ec --;
    vector<string> sg(n);
    for(int i = 0; i < n; i++) cin >> sg[i];
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)  g[i][j] = sg[i][j] - '0';
    }
    vi dr = {-1, 0, 1, 0}, dc = {0, -1, 0, 1};
    vector<vvi> v(4, vvi(n, vi(m, false)));
    v[3][sr][sc] = 1;
    queue<array<int, 3>> q;
    q.push({3, sr, sc});
    while(q.size() != 0) {
        int dir = q.front()[0];
        int r = q.front()[1];
        int c = q.front()[2];
        q.pop();
        // cout << "Q : " << dir << " " << r << " " << c << endl;
        int nrl = r + dr[(dir + 1) % 4];
        int ncl = c + dc[(dir + 1) % 4];
        if(nrl >= 0 && ncl >= 0 && nrl < n && ncl < m && g[nrl][ncl] == 0) {
            if(!v[(dir + 1) % 4][nrl][ncl]) {
                v[(dir + 1) % 4][nrl][ncl] = 1;
                q.push({(dir + 1) % 4, nrl, ncl});
            }
            continue;
        }
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if(nr >= 0 && nc >= 0 && nr < n && nc < n && g[nr][nc] == 0) {
            if(!v[dir][nr][nc]) {
                v[dir][nr][nc] = 1;
                q.push({dir, nr, nc});
            }
            continue;
        }
        if(!v[(dir + 3) % 4][r][c]) {
            v[(dir + 3) % 4][r][c] = 1;
            q.push({(dir + 3) % 4, r, c});
        }
    }
    if(v[0][er][ec] || v[1][er][ec] || v[2][er][ec] || v[3][er][ec]) {
        cout << "1\n";
    }
    else {
        cout << "0\n";
    }
    
    return 0;
}