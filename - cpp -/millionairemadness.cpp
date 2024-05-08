#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - millionairemadness

//we can just use dijkstra's to find the minimum weighted path from start to finish. 
//apparently, you can also use MST to solve this, but i have no idea how

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> g[i][j];
        }
    }
    vector<vector<int>> d(n, vector<int>(m, 2e9));
    priority_queue<pair<int, pair<int, int>>> q;    //{-dist, {r, c}}
    q.push({0, {0, 0}});
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int dist = -q.top().first;
        int r = q.top().second.first;
        int c = q.top().second.second;
        q.pop();
        if(d[r][c] <= dist) {
            continue;
        }
        d[r][c] = dist;
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            int n_dist = max(dist, g[nr][nc] - g[r][c]);
            q.push({-n_dist, {nr, nc}});
        }
    }
    cout << d[n - 1][m - 1] << "\n";
    
    return 0;
}
