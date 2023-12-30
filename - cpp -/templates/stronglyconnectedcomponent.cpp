#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//implementation of kosajaru's algorithm. 
//runs in linear time with respect to the sum of nodes and edges. 
//returns multiple lists of node ids, each list being a scc
vector<vector<int>> find_scc(int n, vector<vector<int>>& adj) {
    vector<vector<int>> adj_rev(n, vector<int>(0));
    vector<bool> used(n, false);
    vector<int> order(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            adj_rev[adj[i][j]].push_back(i);
        }
    }
    function<void(int)> dfs1 = [&used, &adj, &order, &dfs1](int v) -> void {
        used[v] = true;
        for (auto u : adj[v]) {
            if (!used[u]) {
                dfs1(u);
            }
        }
        order.push_back(v);
    };
    for(int i = 0; i < n; i++){
        if(used[i]) {
            continue;
        }
        dfs1(i);
    }
    fill(used.begin(), used.end(), false);
    reverse(order.begin(), order.end());
    function<void(int, vector<int>&)> dfs2 = [&used, &adj_rev, &dfs2](int v, vector<int>& component) -> void {
        used[v] = true;
        component.push_back(v);
        for (auto u : adj_rev[v]) {
            if (!used[u]) {
                dfs2(u, component);
            }
        }
    };
    vector<vector<int>> ans(0);
    for(int i = 0; i < n; i++){
        if(used[order[i]]){
            continue;
        }
        vector<int> component(0);
        dfs2(order[i], component);
        ans.push_back(component);
    }
    return ans;
}

