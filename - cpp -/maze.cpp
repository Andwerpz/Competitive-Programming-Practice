#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 377A

//just figure out how many cells should be empty, and then BFS to fill. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    int nr_empty = 0;
    vector<vector<bool>> g(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            g[i][j] = s[j] == '.';
            nr_empty += g[i][j];
        }
    }
    nr_empty -= k;
    vector<vector<bool>> v(n, vector<bool>(m, false));
    queue<pair<int, int>> q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j]) {
                q.push({i, j});
                break;
            }
        }
        if(q.size()) {
            break;
        }
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while(nr_empty != 0){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        if(v[r][c] || !g[r][c]) {
            continue;
        }
        nr_empty --;
        v[r][c] = true;
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            if(!v[nr][nc] && g[nr][nc]) {
                q.push({nr, nc});
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << (!g[i][j]? "#" : (v[i][j]? "." : "X"));
        }
        cout << "\n";
    }
    
    return 0;
}
