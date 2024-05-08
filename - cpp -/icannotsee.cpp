#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - I

//supposed to be trying all positions of friend, and bipartite matching, but this solution TLE somehow D:

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

//you're fixed at location 0, friends location is passed in. 
map<int, vector<int>> m;
bool check_valid(vector<int>& x, vector<int>& y, int circ, int loc) {
    int n = x.size();
    int ptr = 0;
    vector<int> y_node(n), f_node(n);
    for(int i = 0; i < n; i++){
        y_node[i] = ptr ++;
        f_node[i] = ptr ++;
    }
    int ssource = ptr ++;
    int ssink = ptr ++;
    vector<vector<pair<int, ll>>> c(ptr);
    for(int i = 0; i < n; i++) {
        int p0 = (loc + y[i]) % circ;
        int p1 = (loc + circ - y[i]) % circ;
        vector<int> locs = {p0, p1};
        for(int j = 0; j < 2; j++){
            int pos = locs[j];
            if(m.find(pos) == m.end()) {
                continue;
            }
            for(int k = 0; k < m[pos].size(); k++){
                c[y_node[m[pos][k]]].push_back({f_node[i], 1});
            }
        }
    }
    for(int i = 0; i < n; i++){
        c[ssource].push_back({y_node[i], 1});
        c[f_node[i]].push_back({ssink, 1});
    }
    return dinic(ptr, c, ssource, ssink) == n;
}

int mirror(int x, int c) {
    bool odd = false;
    if(c % 2 == 1){
        odd = true;
        x *= 2;
        c *= 2;
    }
    if(x >= c / 2){
        x -= (x - (c / 2)) * 2;
    }
    else {
        x += ((c / 2) - x) * 2;
    }
    if(odd){
        x /= 2;
    }
    return x;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, c;
    cin >> n >> c;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
        m[x[i]].push_back(i);
        m[c - x[i]].push_back(i);
    }
    int miny = 1e9;
    for(int i = 0; i < n; i++){
        cin >> y[i];
        miny = min(miny, y[i]);
    }
    // cout << "1 " << mirror(1, c) << "\n";
    set<int> works;
    for(int i = 0; i < n; i++){
        int p0 = (x[i] + miny) % c;
        int p1 = (x[i] + c - miny) % c;
        vector<int> t = {p0, p1};
        for(int j = 0; j < t.size(); j++){
            if(check_valid(x, y, c, t[j])) {
                works.insert(t[j]);
                works.insert(mirror(t[j], c) % c);
                // cout << "WORKS : " << t[j] << " " << mirror(t[j], c) << "\n";
            }
        }
    }
    cout << works.size() << "\n";
    
    return 0;
}
