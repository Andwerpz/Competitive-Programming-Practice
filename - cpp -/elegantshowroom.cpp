#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - showroom

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    int sr, sc;
    cin >> sr >> sc;
    sr --;
    sc --;
    priority_queue<pair<int, pair<int, int>>> q;
    vector<vector<int>> d(n, vector<int>(m, 1e9));
    q.push({-1, {sr, sc}});
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int r = q.top().second.first;
        int c = q.top().second.second;
        int dist = -q.top().first;
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
            if(g[nr][nc] == '#'){
                continue;
            }
            int n_dist = dist + (g[nr][nc] == 'c');
            q.push({-n_dist, {nr, nc}});
        }
    }
    int ans = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i == 0 || j == 0 || i == n - 1 || j == m - 1){
                ans = min(ans, d[i][j]);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
