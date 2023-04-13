#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 11 C

//min cut problem, with a twist

//to turn the problem into a max flow problem, we can represent one grid cell as two nodes, an incoming node, and an outgoing node;
//the edge leading from the in node to the out node's capacity is equal to the amount of soldiers required to hold that tile. 

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
    cin >> m >> n;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    int ptr = 0;
    vector<vector<pair<int, int>>> id(n, vector<pair<int, int>>(m, {0, 0}));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            id[i][j].first = ptr ++;
            id[i][j].second = ptr ++;
        }
    }
    int source = ptr ++;
    int sink = ptr ++;
    vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int flow = 10000;
            if('0' <= g[i][j] && g[i][j] <= '9') {
                flow = g[i][j] - '0';
            }
            c[id[i][j].first].push_back({id[i][j].second, flow});
            if(g[i][j] == 'A') {
                c[source].push_back({id[i][j].first, 10000});
            }
            if(g[i][j] == 'B') {
                c[id[i][j].second].push_back({sink, 10000});
            }
            for(int k = 0; k < 4; k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) {
                    continue;
                }
                c[id[i][j].second].push_back({id[nr][nc].first, 10000});
            }
        }
    }
    cout << dinic(ptr, c, source, sink) << "\n";

    return 0;
}
