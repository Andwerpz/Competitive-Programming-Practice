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

//Codeforces - 1000E

//template-forces
//problem boils down to finding the diameter of the block cut tree of the graph. 

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

void _find_diameter_dfs(vector<vector<pair<int, ll>>>& c, vector<ll>& dist, vector<int>& prev, int start) {
    int n = c.size();
    prev = vector<int>(n, -1);
    dist = vector<ll>(n, 1e18);
    vector<bool> v(n, false);
    queue<int> q;
    q.push(start);
    v[start] = true;
    dist[start] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll ndist = c[cur][i].second + dist[cur];
            if(!v[next]) {
                v[next] = true;
                prev[next] = cur;
                dist[next] = ndist;
                q.push(next);
            }
        }
    }
}

vector<vector<pair<int, ll>>> _find_diameter_addweight(vector<vector<int>>& c) {
    vector<vector<pair<int, ll>>> _c(c.size());
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j];
            _c[u].push_back({v, 1});
        }
    }
    return _c;
}

void _find_diameter_dfs(vector<vector<int>>& c, vector<ll>& dist, vector<int>& prev, int start) {
    vector<vector<pair<int, ll>>> _c = _find_diameter_addweight(c);
    _find_diameter_dfs(_c, dist, prev, start);
}

pair<ll, pair<int, int>> find_diameter(vector<vector<pair<int, ll>>>& c){
    vector<ll> dist; vector<int> prev;
    _find_diameter_dfs(c, dist, prev, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, dist, prev, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    ll out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}

pair<ll, pair<int, int>> find_diameter(vector<vector<int>>& c) {
    vector<vector<pair<int, ll>>> _c = _find_diameter_addweight(c);
    return find_diameter(_c);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vvi out_g, out_c;
    find_block_cut_tree(c, out_g, out_c);
    cout << find_diameter(out_c).first << "\n";
    
    return 0;
}