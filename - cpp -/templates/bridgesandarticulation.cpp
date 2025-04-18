#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

vector<bool> find_articulation_points(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
    vector<bool> is_articulation_point(n, false);
    int timer = 0;
    function<void(int, int)> dfs = [&visited, &tin, &low, &is_articulation_point, &timer, &adj, &dfs](int v, int p) -> void {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    is_articulation_point[v] = true;
                ++children;
            }
        }
        if(p == -1 && children > 1)
            is_articulation_point[v] = true;
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i, -1);
    }
    return is_articulation_point;
}

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

//the block cut tree of an undirected graph is when we just compress all the doubly connected components
//into one node, and let the bridges of the original graph form the edges of the tree. 
//out_g consists of the doubly connected components 
//out_c is the edges of the tree connecting the components in out_g
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