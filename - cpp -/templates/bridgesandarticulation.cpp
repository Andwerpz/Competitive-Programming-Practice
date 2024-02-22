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