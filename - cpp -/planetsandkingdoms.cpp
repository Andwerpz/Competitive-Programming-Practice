#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1683

//the problem is just asking you to find strongly connected components. 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
    }
    vector<vector<int>> scc = find_scc(n, c);
    vector<int> ans(n, 0);
    for(int i = 0; i < scc.size(); i++){
        for(int j = 0; j < scc[i].size(); j++){
            ans[scc[i][j]] = i + 1;
        }
    }
    cout << scc.size() << "\n";
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
