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

//Codeforces - 734E

//consider the case where the graph is bipartite. The best way to color all the nodes the same color is to 
//pick one node, and then color it the opposite color. This will make it so that it matches all of it's neighbors. 
//Then continue coloring that component the opposite color until it spreads to the entire tree. We can observe
//that if we select a node halfway along the diameter of the tree, it should give us the minimum moves.  

//Now, we can convert the general case into the bipartite case. We just need to compress all connected components of
//same color down to 1 node. 

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

vector<int> find_diameter_path(vector<vector<int>>& c) {
    pair<int, int> ends = find_diameter(c).second;
    vector<ll> dist; vector<int> prev;
    _find_diameter_dfs(c, dist, prev, ends.first);
    vector<int> path(0);
    int ptr = ends.second;
    while(prev[ptr] != -1){
        path.push_back(ptr);
        ptr = prev[ptr];
    }
    path.push_back(ptr);
    reverse(path.begin(), path.end());
    return path;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vb color(n);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        color[i] = next;
    }
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vvi g(0);
    vi gid(n, -1);
    vb v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        // cout << "I : " << i << endl;
        v[i] = true;
        queue<int> q;
        q.push(i);
        vi cg(0);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            cg.push_back(cur);
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(v[next] || color[next] != color[cur]) {
                    continue;
                }
                v[next] = true;
                q.push(next);
            }
        }
        for(int i = 0; i < cg.size(); i++){
            int next = cg[i];
            gid[next] = g.size();
        }
        g.push_back(cg);
    }
    vvi gc(g.size());
    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j < g[i].size(); j++){
            int cur = g[i][j];
            for(int k = 0; k < c[cur].size(); k++){
                int next = c[cur][k];
                if(gid[next] != i){
                    gc[i].push_back(gid[next]);
                }
            }
        }
    }
    int diam = find_diameter(gc).first;
    cout << (diam + 1) / 2 << "\n";
    
    return 0;
}