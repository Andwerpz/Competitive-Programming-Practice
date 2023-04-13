#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 11 B

//classic bipartite matching. 

//one gopher to one hole

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    vector<pair<int, ll>> edges(0);
    vector<vector<int>> adj(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                ll bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    ld s, v;
    cin >> n >> m >> s >> v;
    while(!cin.eof()) {
        vector<pair<ld, ld>> g(n, {0, 0});
        vector<pair<ld, ld>> h(m, {0, 0});
        for(int i = 0; i < n; i++){
            cin >> g[i].first >> g[i].second;
        }
        for(int i = 0; i < m; i++){
            cin >> h[i].first >> h[i].second;
        }
        vector<vector<pair<int, ll>>> c(n + m + 2, vector<pair<int, ll>>(0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ld dist = sqrt(pow(g[i].first - h[j].first, 2) + pow(g[i].second - h[j].second, 2)) - 1e-10;
                if(dist - s * v < 0) {
                    c[i].push_back({n + j, 1});
                }
            }
        }
        for(int i = 0; i < n; i++){
            c[n + m].push_back({i, 1});
        }
        for(int i = 0; i < m; i++){
            c[n + i].push_back({n + m + 1, 1});
        }
        cout << n - dinic(n + m + 2, c, n + m, n + m + 1) << "\n";
        cin >> n >> m >> s >> v;
    }
    
    return 0;
}
