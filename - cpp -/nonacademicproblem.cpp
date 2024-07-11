#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986F

//it's pretty obvious that we want to remove a bridge, as if we didn't remove a bridge, nothing would happen. 
//note that when we do remove some bridge, the number of connections that we remove is equal to the
//product of the sizes of the two newly formed connected components. 

//so, first thing to do is remove all bridges from the graph, and identify the remaining connected components. 
//In order to quickly determine the maximum amount of connections we can break, we'll represent each
//connected component with a node, and put the nodes in a tree structure with the bridges in the original graph
//acting as the edges of the tree. 

//if edge (u, v) is a bridge, then the returned set should contain {u, v} and {v, u}. 
set<pair<int, int>> find_bridges(int n, vector<vector<int>>& adj) {
    vector<bool> visited;
    vector<int> tin, low;
    int timer;
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    set<pair<int, int>> ans;
    function<void(int, int)> dfs = [&visited, &tin, &low, &timer, &dfs, &adj, &ans](int v, int p) -> void {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v]) {
                    ans.insert({v, to});
                    ans.insert({to, v});
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i, -1);
    }
    return ans;
}

int calc_subt(int cur, vector<vector<int>>& c, vector<int>& subt_size, vector<vector<int>>& g) {
    subt_size[cur] = g[cur].size();
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        subt_size[cur] += calc_subt(next, c, subt_size, g);
    }
    return subt_size[cur];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        set<pair<int, int>> bridges = find_bridges(n, c);
        //remove bridges from c
        {
            vector<vector<int>> tmp(n, vector<int>(0));
            for(int i = 0; i < n; i++){
                for(int j = 0; j < c[i].size(); j++){
                    int next = c[i][j];
                    if(next < i){
                        continue;
                    }
                    if(bridges.count({i, next})) {
                        continue;
                    }
                    tmp[i].push_back(next);
                    tmp[next].push_back(i);
                }
            }
            c = tmp;
        }
        //find connected components
        vector<vector<int>> g(0);
        vector<int> gind(n, -1);
        {
            vector<bool> v(n, false);
            for(int i = 0; i < n; i++){
                if(v[i]) {
                    continue;
                }
                v[i] = true;
                queue<int> q;
                q.push(i);
                g.push_back({});
                while(q.size() != 0){
                    int cur = q.front();
                    q.pop();
                    g[g.size() - 1].push_back(cur);
                    for(int j = 0; j < c[cur].size(); j++){
                        int next = c[cur][j];
                        if(!v[next]) {
                            v[next] = true;
                            q.push(next);
                        }
                    }
                }
            }
            for(int i = 0; i < g.size(); i++){
                // cout << "GROUP : ";
                for(int j = 0; j < g[i].size(); j++){
                    // cout << g[i][j] << " ";
                    gind[g[i][j]] = i;
                }
                // cout << "\n";
            }
        }
        //form connected components into tree structure using bridges
        {
            c = vector<vector<int>>(n, vector<int>(0));
            for(auto i = bridges.begin(); i != bridges.end(); i++){
                int u = i -> first;
                int v = i -> second;
                c[u].push_back(v);
                // cout << "BRIDGE : " << u << " " << v << "\n";
            }
        }
        int _n = g.size();
        vector<vector<int>> _c(_n, vector<int>(0));
        {
            vector<bool> v(_n, false);
            queue<int> q;
            q.push(0);
            v[0] = true;
            while(q.size() != 0){
                int cur = q.front();
                q.pop();
                for(int i = 0; i < g[cur].size(); i++){
                    for(int j = 0; j < c[g[cur][i]].size(); j++){
                        int next = c[g[cur][i]][j];
                        int ngind = gind[next];
                        if(!v[ngind]) {
                            v[ngind] = true;
                            q.push(ngind);
                            _c[cur].push_back(ngind);
                            // cout << "TREE : " << cur << " " << next << endl;
                        }
                    }
                }
            }
        }
        //once we built our tree, compute subtree sizes for each subtree
        vector<int> subt_size(_n, 0);
        calc_subt(0, _c, subt_size, g);
        //calc ans
        ll ans = (ll) n * (ll) (n - 1) / 2ll;
        for(int i = 1; i < g.size(); i++){
            ll cans = (ll) n * (ll) (n - 1) / 2ll;
            cans -= (ll) subt_size[i] * (ll) (n - subt_size[i]);
            ans = min(ans, cans);
            // cout << "SUBT_SIZE : " << subt_size[i] << "\n";
        } 
        cout << ans << "\n";
    }
    
    return 0;
}