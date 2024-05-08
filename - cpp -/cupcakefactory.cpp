#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - I

//we can turn this into a shortest path problem that we can apply dijkstra to. 

//the one issue we have is how to simulate turning on and off the switch. If the switch were permanently on, or 
//permanently off, then it's pretty easy to turn the grid into a graph. 

//therefore, why don't we keep two versions of the graph, one where the switch is on, and one where it is off,
//and use the switches as edges between the two versions of the graph. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        vector<vector<int>> k_off(n, vector<int>(m)), k_on(n, vector<int>(m));
        int ptr = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                k_off[i][j] = ptr ++;
                k_on[i][j] = ptr ++;
            }
        }
        vector<vector<pair<int, int>>> c(ptr, vector<pair<int, int>>(0));  //{node, weight}
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(g[i][j] == '#') {
                    continue;
                }
                //k_off
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(g[nr][nc] == '#') {
                        continue;
                    }
                    c[k_off[i][j]].push_back({k_off[nr][nc], 2});
                }
                //k_on
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(g[nr][nc] == '#') {
                        continue;
                    }
                    if(g[i][j] == '^' && k != 0){
                        continue;
                    }
                    if(g[i][j] == 'v' && k != 1){
                        continue;
                    }
                    if(g[i][j] == '<' && k != 2){
                        continue;
                    }
                    if(g[i][j] == '>' && k != 3) {
                        continue;
                    }
                    int weight = 2;
                    if(g[i][j] == '^' || g[i][j] == 'v' || g[i][j] == '<' || g[i][j] == '>') {
                        weight = 1;
                    }
                    c[k_on[i][j]].push_back({k_on[nr][nc], weight});
                }
                //switch
                if(g[i][j] == '!') {
                    c[k_off[i][j]].push_back({k_on[i][j], 0});
                    c[k_on[i][j]].push_back({k_off[i][j], 0});
                }
            }
        }
        vector<int> dist(ptr, 1e9);
        priority_queue<pair<int, int>> q;   //{-dist, node}
        q.push({0, k_off[0][0]});
        while(q.size() != 0){
            int c_dist = -q.top().first;
            int cur = q.top().second;
            q.pop();
            if(c_dist >= dist[cur]) {
                continue;
            }
            dist[cur] = c_dist;
            for(int i = 0; i < c[cur].size(); i++) {
                int next = c[cur][i].first;
                int weight = c[cur][i].second;
                q.push({-(c_dist + weight), next});
            }
        }
        cout << min(dist[k_off[n - 1][m - 1]], dist[k_on[n - 1][m - 1]]) << "\n";
    }
    
    return 0;
}
