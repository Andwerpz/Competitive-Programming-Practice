#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 11 D

//max flow, but with a twist: we don't want to calculate the instantaneous flow of the system, but the maximum
//amount over a period of time. 

//to do this, instead of having two dimensions, we add another one for time, so now we have a 3D grid of cells, 
//where g[i][j][k] is row i, column j, and at time k. 

//since each person counts as 1, all edges in this graph should have capacity 1. 

//the sources are going to be all the starting positions of the people at t = 0, and the sinks are going to be 
//cells where a[i][j] = 'E', regardless of time; it doesn't matter at what time you reach an exit. 

//to enforce that only one person can be in a tile at one time, we split each node into an in node and an out node, and
//draw an edge of capacity 1 between them

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
    
    int n, m, t;
    cin >> n >> m >> t;
    t ++;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vector<vector<vector<pair<int, int>>>> id(n, vector<vector<pair<int, int>>>(m, vector<pair<int, int>>(t, {0, 0})));
    int ptr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < t; k++){
                id[i][j][k].first = ptr ++;
                id[i][j][k].second = ptr ++;
            }
        }
    }
    int source = ptr ++;
    int sink = ptr ++;
    vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            for(int k = 0; k < t; k++){
                int curIn = id[i][j][k].first;
                int curOut = id[i][j][k].second;
                //link in node to out node
                c[curIn].push_back({curOut, 1});
                if(k != t - 1) {
                    //stay still
                    c[curOut].push_back({id[i][j][k + 1].first, 1});  
                    //move
                    for(int l = 0; l < 4; l++){
                        int nr = i + dr[l];
                        int nc = j + dc[l];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                            continue;
                        }
                        if(g[nr][nc] == '#') {
                            continue;
                        }
                        c[curOut].push_back({id[nr][nc][k + 1].first, 1});
                    }
                }
                if(g[i][j] == 'P' && k == 0) {
                    //connect to source
                    c[source].push_back({curIn, 1});
                }
                if(g[i][j] == 'E') {
                    //connect to sink
                    c[curOut].push_back({sink, 1});
                }
            }
        }
    }
    cout << dinic(ptr, c, source, sink) << "\n";
    
    return 0;
}
