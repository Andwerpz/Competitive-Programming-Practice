#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest O

//if there is a candle that doesn't need to be moved, we can disregard it. 

//we can then use max flow to find the maximum amount of candles that can be moved using 1 move. 

//the remaining candles have to be moved using 2 moves. 

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
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));
    vector<vector<int>> b(n, vector<int>(n, 0));
    vector<vector<int>> aid(n, vector<int>(n, 0));
    vector<vector<int>> bid(n, vector<int>(n, 0));
    int ptr = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
            aid[i][j] = ptr ++;
            sum += a[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> b[i][j];
            bid[i][j] = ptr ++;
            int sub = min(b[i][j], a[i][j]);
            b[i][j] -= sub;
            a[i][j] -= sub;
            sum -= sub;
        }
    }
    int source = ptr ++;
    int sink = ptr ++;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            //cout << "FROM SOURCE : " << source << " " << aid[i][j] << "\n";
            c[source].push_back({aid[i][j], a[i][j]});
            for(int k = 0; k < n; k++){
                //cout << "SHARE COL : " << aid[i][j] << " " << bid[k][j] << "\n";
                //cout << "SHARE ROW : " << aid[i][j] << " " << bid[i][k] << "\n";
                c[aid[i][j]].push_back({bid[k][j], a[i][j]});
                c[aid[i][j]].push_back({bid[i][k], a[i][j]});
            }
            //cout << "TO SINK : " << bid[i][j] << " " << sink << "\n";
            c[bid[i][j]].push_back({sink, b[i][j]});
        }
    }
    ll single = dinic(ptr, c, source, sink);
    ll ans = single + (sum - single) * 2;
    cout << ans << "\n";
    //cout << single << "\n";
    
    return 0;
}
