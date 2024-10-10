#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - espressobucks

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vector<vector<char>> color(n, vector<char>(m, '#'));
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == '#') {
                continue;
            }
            if(color[i][j] != '#') {
                continue;
            }
            queue<pair<int, int>> q;
            q.push({i, j});
            color[i][j] = 'E';
            while(q.size() != 0){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(g[nr][nc] == '#' || color[nr][nc] != '#') {
                        continue;
                    }
                    color[nr][nc] = color[r][c] == '.'? 'E' : '.';
                    q.push({nr, nc});
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << color[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}
