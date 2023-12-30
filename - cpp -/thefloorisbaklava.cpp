#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 F

//this can be turned into a max flow probem. 

//each cell is just a junction that can handle at most k[i][j] flow through it. Each junction has connections
//to it's neighboring cells, and the source and sink are positioned at coordinates (0, 0) and (n - 1, m - 1). 

//the answer is simply the maximum amount of flow that can get from source to sink. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> k(n, vector<ll>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> k[i][j];
        }
    }
    k[0][0] = 1e10;
    k[n - 1][m - 1] = 1e10;
    vector<vector<int>> g_in(n, vector<int>(m, 0));
    vector<vector<int>> g_out(n, vector<int>(m, 0));
    int ptr = 0;
    int ssource = ptr ++;
    int ssink = ptr ++;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            g_in[i][j] = ptr ++;
            g_out[i][j] = ptr ++;
        }
    }
    vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
    //ssource to 0, 0
    c[ssource].push_back({g_in[0][0], 1e10});
    //internal grid conn
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            c[g_in[i][j]].push_back({g_out[i][j], k[i][j]});
        }
    }
    //external grid conn
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < 4; k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                c[g_out[i][j]].push_back({g_in[nr][nc], 1e10});
            }
        }
    }
    //exit to ssink
    c[g_out[n - 1][m - 1]].push_back({ssink, 1e10});
    cout << dinic(ptr, c, ssource, ssink) << "\n";
    
    return 0;
}
