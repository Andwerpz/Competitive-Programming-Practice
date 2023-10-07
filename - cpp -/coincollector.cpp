#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1686

//first, we can turn the graph into a DAG by grouping all SCC's together. 

//next, we notice that it is never optimal to start at a node with an indegree that is not 0. To prove this, notice
//if we do start at a node with indegree 1 or greater, then we can always increase our answer by just starting at a node
//that can go to the node we originally started at. 

//then, the answer is to do a dp with base cases at nodes with indegree 0; where dp[i] is equal to the maximum
//number of coins that you can collect once you visit node i. 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<ll> coins(n);
    for(int i = 0; i < n; i++){
        cin >> coins[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
    }
    vector<vector<int>> scc = find_scc(n, c);
    vector<ll> scc_coins(scc.size(), 0);
    vector<vector<int>> scc_c(scc.size(), vector<int>(0));
    map<int, int> scc_map;
    for(int i = 0; i < scc.size(); i++){
        for(int j = 0; j < scc[i].size(); j++){
            scc_map.insert({scc[i][j], i});
            scc_coins[i] += coins[scc[i][j]];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int a = scc_map[i];
            int b = scc_map[c[i][j]];
            if(a != b){
                scc_c[a].push_back(b);
            }
        }
    }
    vector<int> nr_in(scc.size(), 0);
    for(int i = 0; i < scc_c.size(); i++){
        for(int j = 0; j < scc_c[i].size(); j++){
            nr_in[scc_c[i][j]] ++;
        }
    }
    vector<ll> dp(scc.size(), 0);
    queue<int> q;
    for(int i = 0; i < scc.size(); i++){
        if(nr_in[i] == 0){
            q.push(i);
        }
    }
    ll ans = 0;
    while(q.size()) {
        int cur = q.front();
        q.pop();
        dp[cur] += scc_coins[cur];
        ans = max(ans, dp[cur]);
        for(int i = 0; i < scc_c[cur].size(); i++){
            int next = scc_c[cur][i];
            nr_in[next] --;
            dp[next] = max(dp[next], dp[cur]);
            if(nr_in[next] == 0){
                q.push(next);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
