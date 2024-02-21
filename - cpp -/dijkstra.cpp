#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 20C

//dijkstra with a lil bit of backtracking. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        a --;
        b --;
        c[a].push_back({b, w});
        c[b].push_back({a, w});
    }
    vector<ll> dist(n, 1e18);
    priority_queue<pair<ll, pair<int, int>>> q; //{-current path length, {prev id, node id}}
    q.push({0, {-1, 0}});
    vector<int> parent(n, -1);
    while(q.size() != 0){
        int prev = q.top().second.first;
        int cur = q.top().second.second;
        ll cur_dist = -q.top().first;
        q.pop();
        if(cur_dist >= dist[cur]) {
            continue;
        }
        dist[cur] = cur_dist;   
        parent[cur] = prev;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll n_dist = cur_dist + c[cur][i].second;
            if(n_dist < dist[next]) {
                q.push({-n_dist, {cur, next}});
            }
        }
    }
    if(dist[n - 1] == 1e18) {
        cout << "-1\n";
        return 0;
    }
    vector<int> path(0);
    int ptr = n - 1;
    while(ptr != -1){
        path.push_back(ptr);
        ptr = parent[ptr];
    }
    reverse(path.begin(), path.end());
    for(int i = 0; i < path.size(); i++){
        cout << path[i] + 1 << " \n"[i == path.size() - 1];
    }
    
    return 0;
}
