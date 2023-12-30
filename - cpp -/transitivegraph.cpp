#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1900E

//observe that if there is an SCC in G, then in H, we can visit all the nodes in the SCC using a simple path. 

//thus, we can find all SCCs in G and compress them, turning G into a DAG. Then, we do topological dp over the DAG to
//find the longest simple path with the least value along the path. 

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
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
        }
        vector<vector<int>> scc = find_scc(n, c);
        vector<int> node_scc(n, -1);
        n = scc.size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < scc[i].size(); j++){
                node_scc[scc[i][j]] = i;
            }
        }
        vector<vector<int>> scc_c(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < scc[i].size(); j++){
                int cur = scc[i][j];
                for(int k = 0; k < c[cur].size(); k++){
                    int next = c[cur][k];
                    if(node_scc[cur] != node_scc[next]) {
                        int u = node_scc[cur];
                        int v = node_scc[next];
                        scc_c[u].push_back(v);
                    }
                }
            }
        }
        vector<pair<ll, ll>> val(n);
        for(int i = 0; i < n; i++){
            pair<ll, ll> cur = {scc[i].size(), 0};
            for(int j = 0; j < scc[i].size(); j++){
                cur.second += a[scc[i][j]];
            }
            val[i] = cur;
        }
        vector<int> indeg(n, 0);
        queue<int> q;
        vector<pair<ll, ll>> dp(n, {0, 0});  //{nr nodes, total value}
        for(int i = 0; i < n; i++){
            for(int j = 0; j < scc_c[i].size(); j++){
                int next = scc_c[i][j];
                indeg[next] ++;
            }
        }
        for(int i = 0; i < n; i++){
            if(indeg[i] == 0){
                q.push(i);
            }
        }
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            dp[cur].first += val[cur].first;
            dp[cur].second += val[cur].second;
            for(int i = 0; i < scc_c[cur].size(); i++){
                int next = scc_c[cur][i];
                indeg[next] --;
                if(indeg[next] == 0){
                    q.push(next);
                }
                if(dp[next].first < dp[cur].first) {
                    dp[next] = dp[cur];
                }
                if(dp[next].first == dp[cur].first && dp[next].second > dp[cur].second) {
                    dp[next] = dp[cur];
                }
            }
        }
        pair<ll, ll> ans = {0, 1e18};
        for(int i = 0; i < n; i++){
            if(dp[i].first > ans.first) {
                ans = dp[i];
            }
            if(dp[i].first == ans.first && dp[i].second < ans.second) {
                ans = dp[i];
            }
        }
        cout << ans.first << " " << ans.second << "\n";
    }
    
    return 0;
}
