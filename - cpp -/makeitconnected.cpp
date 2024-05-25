#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1761E

//if there is a node that is not connected to any other node, we can just do the operation on that one, and call it a day. 

//otherwise, we can first find all of the connected components in the graph. If there is a component that not a clique, 
//then it's guaranteed that there is a node within that component that if you do the operation on it, it will connect the 
//entire graph. (look at the editorial for more info and proof)

//otherwise, all of the components are cliques. If there are exactly 2 cliques, then doing the operation on one node will
//just transfer it to the other clique, so you need to do the operation on all nodes in a clique. 

//otherwise, there are >= 3 cliques. In this case, you can just pick 2 nodes from different cliques, and do the operation
//on those two. 

//of course, at the beginning you need to check if they are all initially connected. 

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

vector<int> solve(int n, vector<vector<int>>& c) {
    //if there is only one element, do nothing
    if(n == 1){
        return {};
    }
    //find all connected components
    vector<vector<int>> g(0);
    vector<int> gid(n, -1);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        vector<int> cg(0);
        v[i] = true;
        queue<int> q;
        q.push(i);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            cg.push_back(cur);
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(v[next]) {
                    continue;
                }
                v[next] = true;
                q.push(next);
            }
        }
        for(int j = 0; j < cg.size(); j++){
            gid[cg[j]] = g.size();
        }
        g.push_back(cg);
        if(cg.size() == 1){
            //if there is a component of size 1, we can just do an operation on this one
            return {i};
        }
    }
    //if it's just 1 component, do nothing
    if(g.size() == 1){
        return {};
    }
    //check if there exists a component that is not a clique
    for(int i = 0; i < g.size(); i++){
        bool is_clique = true;
        for(int j = 0; j < g[i].size(); j++){
            int cur = g[i][j];
            if(c[cur].size() != g[i].size() - 1) {
                is_clique = false;
            }
        }
        if(is_clique) {
            continue;
        }
        //ok, this one is not a clique, find the node that is not an articulation point, 
        //that is also not connected to all other nodes in the component
        vector<bool> is_art = find_articulation_points(n, c);
        for(int j = 0; j < g[i].size(); j++){
            int cur = g[i][j];
            if(is_art[cur]) {
                continue;
            }
            if(c[cur].size() == g[i].size() - 1) {
                continue;
            }
            return {cur};
        }
    }
    //they are all cliques. If there are only 2 cliques, take the minimum one
    if(g.size() == 2){
        return g[0].size() <= g[1].size()? g[0] : g[1];
    }
    //otherwise 3 or more cliques. just do the operation on two elements of different cliques
    return {g[0][0], g[1][0]};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = i + 1; j < n; j++){
                if(s[j] == '1') {
                    c[i].push_back(j);
                    c[j].push_back(i);
                }
            }
        }
        vector<int> ans = solve(n, c);
        cout << ans.size() << "\n";
        if(ans.size() != 0){
            for(int i = 0; i < ans.size(); i++){
                cout << ans[i] + 1 << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}