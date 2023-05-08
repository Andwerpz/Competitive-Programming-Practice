#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 I

//dijkstra's over the grid, and time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, e;
    cin >> n >> m >> e;
    vector<string> g(n);
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(50 * 50 + 10, 1e9)));
    priority_queue<tuple<int, int, int, int>> q;
    for(int i = 0; i < n; i++){
        cin >> g[i];
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'S'){
                q.push({0, 0, i, j});
                dist[i][j][0] = 0;
            }
        }
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    bool isValid = false;
    int ans = 1e9;
    while(q.size() != 0){
        int k = -get<0>(q.top());
        int r = get<2>(q.top());
        int c = get<3>(q.top());
        int d = dist[r][c][k];
        q.pop();
        if(g[r][c] == 'G'){
            isValid = true;
            ans = min(ans, k + 1);
        }
        //try resting
        if(k != dist[r][c].size() - 1){
            if(dist[r][c][k + 1] != 0){
                dist[r][c][k + 1] = 0;
                q.push({-(k + 1), 0, r, c});
            }
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
            int nDist = d;
            if(g[nr][nc] == '.' || g[nr][nc] == 'G'){
                nDist += 1;
            }
            else if(g[nr][nc] == 'F'){
                nDist += 2;
            }
            else if(g[nr][nc] == 'M'){
                nDist += 3;
            }
            if(nDist > e){
                continue;
            }
            if(dist[nr][nc][k] <= nDist) {
                continue;
            }
            dist[nr][nc][k] = nDist;
            q.push({-k, -nDist, nr, nc});
        }
    }
    if(isValid){
        cout << ans << "\n";
    }
    else {
        cout << "-1\n";
    }
    
    return 0;
}
