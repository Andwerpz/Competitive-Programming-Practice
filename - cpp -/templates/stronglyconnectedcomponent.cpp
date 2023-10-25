#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

void find_scc_dfs1(int v, vector<bool>& used, vector<vector<int>>& adj, vector<int>& order) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            find_scc_dfs1(u, used, adj, order);

    order.push_back(v);
}

void find_scc_dfs2(int v, vector<bool>& used, vector<vector<int>>& adj_rev, vector<int>& component) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            find_scc_dfs2(u, used, adj_rev, component);
}

//implementation of kosajaru's algorithm. 
//runs in linear time with respect to the sum of nodes and edges. 
vector<vector<int>> find_scc(int n, vector<vector<int>>& adj) {
    vector<vector<int>> adj_rev(n, vector<int>(0));
    vector<bool> used(n, false);
    vector<int> order(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            adj_rev[adj[i][j]].push_back(i);
        }
    }
    for(int i = 0; i < n; i++){
        if(used[i]) {
            continue;
        }
        find_scc_dfs1(i, used, adj, order);
    }
    fill(used.begin(), used.end(), false);
    reverse(order.begin(), order.end());
    vector<vector<int>> ans(0);
    for(int i = 0; i < n; i++){
        if(used[order[i]]){
            continue;
        }
        vector<int> component(0);
        find_scc_dfs2(order[i], used, adj_rev, component);
        ans.push_back(component);
    }
    return ans;
}

