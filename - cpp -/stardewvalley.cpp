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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1994F

//the problem boils down to finding an eulerian cycle on the graph, where we have some edges that we are allowed to remove. 
//an eulerian cycle exists on an undirected graph if all the nodes have an even degree, and the graph is connected. 

//first, we can compute the degree of every node, and then only consider the edges we are allowed to remove. For each connected
//component considering only edges without NPCs, create a rooted spanning tree. The idea is that if the degree of a node in the 
//tree is odd, then we can make it even by removing the node connecting it to it's parent. Note that this will only make all 
//nodes in the tree even if the number of odd nodes is even, as removing an edge changes the parity of two nodes. 

//finally, if we manage to make all node degrees even, then we can simply find the eulerian cycle. 

void dfs(int cur, int p, vector<vector<pii>>& c, int pedge, vb& v, vb& er, vi& deg) {
    v[cur] = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        int eid = c[cur][i].second;
        if(v[next]) {
            continue;
        }
        dfs(next, cur, c, eid, v, er, deg);
    }
    if(deg[cur] % 2 == 1 && p != -1) {
        deg[cur] --;
        deg[p] --;
        er[pedge] = true;
    }
}

void euler_path_undirected(vector<vector<int>>& c, vector<vector<int>>& eid, vector<int>& ptr, vector<bool>& rm, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()){
        if(rm[eid[i][ptr[i]]]){
            ptr[i] ++;
            continue;
        }
        int next = c[i][ptr[i]];
        rm[eid[i][ptr[i]]] = true;
        ptr[i] ++;
        euler_path_undirected(c, eid, ptr, rm, ans, next);
    }
    ans.push_back(i);
}

vector<int> euler_path_undirected(vector<vector<int>>& _c, int i){
    int n = _c.size();
    int m = 0;
    vector<vector<int>> eid(n), c(n);
    vector<int> ptr(n, 0), ans(0);
    vector<bool> se(n, false);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < _c[i].size(); j++){
            int next = _c[i][j];
            if(next >= i){
                if(next == i){
                    se[i] = !se[i];
                    if(!se[i]){
                        continue;
                    }
                }
                eid[i].push_back(m);
                c[i].push_back(next);
                eid[next].push_back(m);
                c[next].push_back(i);
                m ++;
            }
        }
    }
    vector<bool> rm(m, false);
    euler_path_undirected(c, eid, ptr, rm, ans, i);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<pii> e(0);
        vector<vector<pii>> cb(n);
        vi deg(n, 0);
        for(int i = 0; i < m; i++){
            int u, v, c;
            cin >> u >> v >> c;
            u --;
            v --;
            e.push_back({u, v});
            deg[u] ++;
            deg[v] ++;
            if(!c) {
                cb[u].push_back({v, i});
                cb[v].push_back({u, i});
            }
        }   
        vb v(n, false), er(m, false);
        for(int i = 0; i < n; i++){
            if(v[i]){
                continue;
            }
            dfs(i, -1, cb, -1, v, er, deg);
        }
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            if(deg[i] % 2) {
                is_valid = false;
            }
        }
        if(!is_valid) {
            cout << "NO\n";
            continue;
        }
        vvi c(n);
        for(int i = 0; i < m; i++){
            if(!er[i]) {
                int u = e[i].first;
                int v = e[i].second;
                c[u].push_back(v);
                c[v].push_back(u);
            }
        }
        vi ans = euler_path_undirected(c, 0);
        cout << "YES\n";
        cout << ans.size() - 1 << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] + 1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}