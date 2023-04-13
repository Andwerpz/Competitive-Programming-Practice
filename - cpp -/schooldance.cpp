#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1696

//classic bipartite matching problem

vector<pair<int, ll>> edges;
vector<vector<int>> adj;

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    edges = vector<pair<int, ll>>(0);
    adj = vector<vector<int>>(n, vector<int>(0));
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
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, ll>>> c(n + m + 2, vector<pair<int, ll>>(0));
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back({n + b, 1});
        //cout << "EDGE : " << a << " " << n + b << "\n";
    }
    for(int i = 0; i < n; i++){
        c[n + m].push_back({i, 1});
        //cout << "EDGE : " << n + m << " " << i << "\n";
    }
    for(int i = 0; i < m; i++){
        c[n + i].push_back({n + m + 1, 1});
        //cout << "EDGE : " << n + i << " "<< n + m + 1 << "\n";
    }
    dinic(n + m + 2, c, n + m, n + m + 1);
    vector<pair<int, int>> ans(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            int nEdge = adj[i][j];
            ll flow = edges[nEdge].second;
            int dest = edges[nEdge].first;
            if(flow == 0 && dest - n >= 0 && dest - n < m){
                //we're using it
                ans.push_back({i, dest - n});
            }
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}
