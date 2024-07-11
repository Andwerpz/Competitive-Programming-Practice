#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 732F

//intuitively, if we want to raise the minimum, then we should find the largest cycle that we can make
//and then have all the other nodes get visited off of that cycle. 

//first, notice that any bridge cannot be part of a cycle, so we can first just remove those from the graph.
//Actually, what we want to find is the block cut tree representation of the graph. We'll choose the largest
//doubly connected component to be the set of nodes that can visit everyone else. 

//in order to make sure that each doubly connected component becomes an scc in the final directed graph, we can
//simply do a dfs through the undirected graph. Everytime we move from some node a -> b, we'll just direct the edge
//there from a -> b. 

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

void find_block_cut_tree(vector<vector<int>> c, vector<vector<int>>& out_g, vector<vector<int>>& out_c) {
    set<pair<int, int>> bridges = find_bridges(c.size(), c);
    int n = c.size();
    //remove bridges
    {
        vector<vector<int>> tmp(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                int u = i;
                int v = c[i][j];
                if(!bridges.count({u, v})) {
                    tmp[u].push_back(v);
                }
            }
        }
        c = tmp;
    }
    //find connected components
    out_g = vector<vector<int>>(0);
    vector<int> gind(n, -1);
    {
        vector<int> v(n, false);
        for(int i = 0; i < n; i++){
            if(v[i]) {
                continue;
            }
            v[i] = true;
            queue<int> q;
            q.push(i);
            out_g.push_back({});
            while(q.size() != 0){
                int cur = q.front();
                q.pop();
                out_g.rbegin()->push_back(cur);
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j];
                    if(!v[next]) {
                        v[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        for(int i = 0; i < out_g.size(); i++){
            for(int j = 0; j < out_g[i].size(); j++){
                gind[out_g[i][j]] = i;
            }
        }
    }
    //find tree
    out_c = vector<vector<int>>(out_g.size(), vector<int>(0));
    for(auto i = bridges.begin(); i != bridges.end(); i++){
        int u = i->first;
        int v = i->second;
        u = gind[u];
        v = gind[v];
        out_c[u].push_back(v);
    }
}

void do_dfs(int cur, vector<vector<int>>& c, vector<bool>& v, vector<bool>& ve, map<pair<int, int>, int>& ind_mp, vector<pair<int, int>>& ans) {
    if(v[cur]) {
        return;
    }
    v[cur] = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        int eind = ind_mp[{cur, next}];
        if(!ve[eind]) {
            ve[eind] = true;
            ans[eind] = {next, cur};
        }
        do_dfs(next, c, v, ve, ind_mp, ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    map<pair<int, int>, int> ind_mp;
    vector<pair<int, int>> ans(m);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
        ind_mp.insert({{u, v}, i});
        ind_mp.insert({{v, u}, i});
    }
    vector<vector<int>> g, tc;
    find_block_cut_tree(c, g, tc);
    //start from largest connected component and dfs outwards
    int lg_ind = 0;
    for(int i = 0; i < g.size(); i++){
        if(g[i].size() > g[lg_ind].size()) {
            lg_ind = i;
        }
    }
    vector<bool> v(n, false), ve(ans.size(), false);
    do_dfs(g[lg_ind][0], c, v, ve, ind_mp, ans);
    cout << g[lg_ind].size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}