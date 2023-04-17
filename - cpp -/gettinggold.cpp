#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 B

//do dfs, but if you're next to a trap, then you can't visit any new nodes. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> m >> n;
    vector<string> g(n);
    pair<int, int> start = {};
    for(int i = 0; i < n; i++){
        cin >> g[i];
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'P'){
                start = {i, j};
            }
        }
    }
    stack<pair<int, int>> s;
    vector<vector<bool>> v(n, vector<bool>(m, false));
    v[start.first][start.second] = true;
    s.push(start);
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int ans = 0;
    while(s.size() != 0){
        int r = s.top().first;
        int c = s.top().second;
        s.pop();
        ans += g[r][c] == 'G';
        bool draft = false;
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(g[nr][nc] == '#'){
                continue;
            }
            if(g[nr][nc] == 'T'){
                draft = true;
            }
        }
        if(draft) {
            continue;
        }
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(g[nr][nc] == '#') {
                continue;
            }
            if(v[nr][nc]) {
                continue;
            }
            if(g[nr][nc] == '.' || g[nr][nc] == 'G') {
                s.push({nr, nc});
                v[nr][nc] = true;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
