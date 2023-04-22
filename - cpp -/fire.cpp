#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 D

//calculate the minimum dist from each cell to the nearest fire. 

//then use that to path joe through the maze. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vector<vector<int>> tFire(n, vector<int>(m, 1e9));
    vector<vector<int>> tJoe(n, vector<int>(m, 1e9));
    queue<pair<int, int>> q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'F') {
                q.push({i, j});
                tFire[i][j] = 1;
            }
        }
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        int time = tFire[r][c];
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            if(g[nr][nc] == '#'){
                continue;
            }
            if(tFire[nr][nc] <= time + 1){
                continue;
            }
            tFire[nr][nc] = time + 1;
            q.push({nr, nc});
        }
        //cout << r << " " << c << endl;
    }
    //cout << "DONE FIRE " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'J'){
                q.push({i, j});
                tJoe[i][j] = 1;
            }
        }
    }
    bool isValid = false;
    int ans = 1e9;
    while(q.size() != 0){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        int time = tJoe[r][c];
        if(r == 0 || c == 0 || r == n - 1 || c == m - 1){
            isValid = true;
            ans = min(ans, time);
        }
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            if(g[nr][nc] == '#'){
                continue;
            }
            if(tFire[nr][nc] <= time + 1){
                continue;
            }
            if(tJoe[nr][nc] <= time + 1){
                continue;
            }
            tJoe[nr][nc] = time + 1;
            q.push({nr, nc});
        }
    }
    if(isValid){
        cout << ans << "\n";
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
