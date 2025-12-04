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

//ICPC NAC 2021 - L

//first, we can do one dijkstra pass to find for each node the shortest distance from node 1

//then we can do a second dijkstra pass with knowledge of the shortest distances to each node. First, sort all of
//the travelog entries, as they must appear in sorted order. Then, for each node, keep track of the index in which
//the travelog should be at that node. Since we know that Bob travelled along a shortest path from 1 to n, 
//the index should be unique for every node. 

//We also keep track of the number of paths ending at each node, and one previous node back to 1. If there is a 
//unique path, we can use this previous node array to reconstruct the path. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<pll>> c(n);
    {
        map<int, map<int, ll>> emp;
        for(int i = 0; i < m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            u --, v --;
            if(!emp[u].count(v)) emp[u][v] = cost;
            emp[u][v] = min(emp[u][v], (ll) cost);
        }
        for(int i = 0; i < n; i++){
            for(auto j = emp[i].begin(); j != emp[i].end(); j++){
                // cout << "EDGE : " << i << " " << j->first << " " << j->second << "\n";
                c[i].push_back({(ll) j->first, j->second});
            }
        }
    }
    vl t(d);
    for(int i = 0; i < d; i++) cin >> t[i];
    sort(t.begin(), t.end());
    vl dist(n, 2e18);
    {
        dist[0] = 0;
        priority_queue<pll> q;  //{-dist, ind};
        q.push({0, 0});
        vb v(n, false);
        while(q.size() != 0){
            int cur = q.top().second;
            ll cdist = -q.top().first;
            q.pop();
            if(cdist != dist[cur]) continue;
            if(v[cur]) continue;
            v[cur] = true;
            for(pll x : c[cur]) {
                ll ndist = cdist + x.second;
                int next = x.first;
                if(ndist < dist[next]) {
                    dist[next] = ndist;
                    q.push({-ndist, next});
                }
            }
        }
    }
    vl pcnt(n, 0);
    pcnt[0] = 1;
    vi prev(n, -1), dind(n, -1);
    dind[0] = t[0] == 0? 1 : 0;
    {
        priority_queue<pll> q;
        q.push({0, 0});
        vb v(n, false);
        v[0] = true;
        while(q.size() != 0){
            int cur = q.top().second;
            ll cdist = -q.top().first;
            q.pop();
            // cout << "BFS : " << cur << "\n";
            for(pll x : c[cur]) {
                ll ndist = cdist + x.second;
                int next = x.first;
                if(dist[next] == ndist) {   //on shortest path
                    // cout << "SHORT : " << next << " " << ndist << "\n";
                    if(dind[cur] != d && ndist > t[dind[cur]]) goto out;    //doesn't match with travelog
                    if(dind[cur] != d) dind[next] = ndist == t[dind[cur]]? dind[cur] + 1 : dind[cur];
                    else dind[next] = dind[cur];
                    if(!v[next]) {
                        v[next] = true;
                        q.push({-ndist, next});
                    }
                    pcnt[next] += pcnt[cur];
                    pcnt[next] = min(pcnt[next], (ll) 1e6);
                    prev[next] = cur;
                }
                out: {};
            }
        }
    }
    if(pcnt[n - 1] == 0 || dind[n - 1] != d) cout << "0\n";
    else if(pcnt[n - 1] > 1) cout << "1\n";
    else {
        vi path;
        int ptr = n - 1;
        while(ptr != -1) {
            path.push_back(ptr);
            ptr = prev[ptr];
        }
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for(int x : path) cout << x + 1 << "\n";
    }
    
    return 0;
}