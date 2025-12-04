#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

// BAPC 2023 - L

//first, lets make the assumption that the given graph is a DAG. 
//we can make the observation that the minimum number of exits we must insert is equal to the amount of 
//nodes that have indeg 0. 

//next, lets make the assumption that the given graph is a SCC. 
//here, I made the (i think reasonable) guess that for any SCC, the minimum amount of exits is 1, and actually
//we can place this exit anywhere and it'll always work. 

//so to solve the full problem, create the DAG graph out of the given graph by merging all the SCCs, and then 
//find how many nodes have indeg 0

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
    }
    vvi scc = find_scc(n, c);
    int sn = scc.size();
    vvi sc(sn);
    vi scc_id(n);
    for(int i = 0; i < scc.size(); i++) for(int x : scc[i]) scc_id[x] = i;
    vi indeg(sn, 0);
    for(int i = 0; i < n; i++) {
        int scur = scc_id[i];
        for(int x : c[i]) {
            int sx = scc_id[x];
            if(scur != sx) indeg[sx] ++;
        }
    }
    int ans = 0;
    for(int i = 0; i < sn; i++) {
        if(indeg[i] == 0) ans ++;
    }
    cout << ans << "\n";
    
    return 0;
}