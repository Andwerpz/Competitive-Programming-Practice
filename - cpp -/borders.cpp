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

//ICPC NAC 2021 - C

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    //identify all components, assign ids
    int idptr = 0;
    vvi id(n, vi(m, -1));
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) g[i][j] = s[j] - '0';
    }
    vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(id[i][j] != -1) continue;
            queue<pii> q;
            q.push({i, j});
            id[i][j] = idptr ++;
            while(q.size() != 0){
                int r = q.front().first, c = q.front().second;
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k], nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc > m) continue;
                    if(id[nr][nc] != -1) continue;
                    if(g[nr][nc] != g[r][c]) continue;
                    id[nr][nc] = id[r][c];
                    q.push({nr, nc});
                }
            }
        }
    }

    
    return 0;
}