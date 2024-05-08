#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - avoidingtheapocalypse

//max flow problem. We can represent the situation as a max flow graph. 

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
    cin.tie(NULL); cout.tie(NULL);
    
    int _t;
    cin >> _t;
    while(_t--){
        int n;
        cin >> n;
        int _i, g, s;
        cin >> _i >> g >> s;
        _i --;
        int m;
        cin >> m;
        vector<bool> is_med(n, false);
        for(int i = 0; i < m; i++){
            int next;
            cin >> next;
            is_med[next - 1] = true;
        }
        int r;
        cin >> r;
        vector<vector<pair<int, ll>>> c_p(n), c_t(n);
        for(int i = 0; i < r; i++){
            int a, b, p, t;
            cin >> a >> b >> p >> t;
            a --;
            b --;
            c_p[a].push_back({b, p});
            c_t[a].push_back({b, t});
        }
        vector<vector<int>> node(n, vector<int>(s + 1));
        int ptr = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= s; j++){
                node[i][j] = ptr ++;
            }
        }
        int ssource = ptr ++;
        int ssink = ptr ++;
        vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
        //source to start
        c[ssource].push_back({node[_i][0], g});
        //graph connections
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= s; j++){
                for(int k = 0; k < c_p[i].size(); k++){
                    int next = c_p[i][k].first;
                    int cap = c_p[i][k].second;
                    int next_time = j + c_t[i][k].second;
                    if(next_time <= s){
                        c[node[i][j]].push_back({node[next][next_time], cap});
                    }
                }
                //self to self
                if(j != s) {
                    c[node[i][j]].push_back({node[i][j + 1], 1e9});
                }
            }
        }
        //med to sink
        for(int i = 0; i < n; i++){
            if(!is_med[i]) {
                continue;
            }
            for(int j = 0; j <= s; j++){
                c[node[i][j]].push_back({ssink, 1e9});
            }
        }
        cout << dinic(ptr, c, ssource, ssink) << "\n";
    }
    
    return 0;
}
