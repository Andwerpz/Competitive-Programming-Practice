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

//Codeforces - 1182D

//given some root, we can test whether or not it's valid in n * log(n) time. My idea revolves around the 
//fact that we only have to test very few nodes until we can say there is no answer. 

//first, if the root has degree higher than 1, then it must fall on the midpoint of the diameter of the tree. 
//This is true because the root must have the same distance to all leaf nodes. 

//otherwise, the root is a leaf. In this case, it could be at the end of a diameter. However, the more tricky 
//case is when it's not on the diameter at all. In order for this to be the case, the diameter must have 
//odd size. Denote mid as the midpoint of the diameter. The leaf root must be connected to mid via a 
//chain of nodes. We can find this using hashing (which is overkill), or dfs. 

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

void dfs(int cur, int p, vvi& c, vi& dist) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dist[next] = dist[cur] + 1;
        dfs(next, cur, c, dist);
    }
}

bool is_valid(vvi& c, vi& deg, int root) {
    int n = c.size();
    vi dist(n);
    dist[root] = 0;
    dfs(root, -1, c, dist);
    map<int, int> m;
    for(int i = 0; i < n; i++){
        if(!m.count(dist[i])) {
            m[dist[i]] = deg[i];
        }
        if(m[dist[i]] != deg[i]) {
            return false;
        }
    }
    return true;
}

ll pr1 = 71, pr2 = 13;
ll mod = 1e9 + 7;
ll subt_hash(int cur, int p, vvi& c, ll pr){
    vl child(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        child.push_back(subt_hash(next, cur, c, pr));
    }
    sort(child.begin(), child.end());
    ll hash = 1;
    for(int i = 0; i < child.size(); i++){
        hash = (hash * pr + child[i]) % mod;
    }
    return hash;
}

ll subt_hash(int cur, int p, vvi& c) {
    return subt_hash(cur, p, c, pr1) | (subt_hash(cur, p, c, pr2) << 31);
}

void get_leaf(int cur, int p, vvi& c, vi& ans) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        get_leaf(next, cur, c, ans);
    }
    if(c[cur].size() == 1){
        ans.push_back(cur);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    vi deg(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --; 
        c[u].push_back(v);
        c[v].push_back(u);
        deg[u] ++;
        deg[v] ++;
    }
    vi path = find_diameter_path(c);
    vi cand = {path[0], path[path.size() - 1]};
    if(path.size() % 2 == 1) {
        int mid = path[path.size() / 2];
        // cout << "MID : " << mid << "\n";
        cand.push_back(mid);
        map<ll, int> m;
        for(int i = 0; i < c[mid].size(); i++){
            int next = c[mid][i];
            m[subt_hash(next, mid, c)] ++;
            // cout << subt_hash(next, mid, c) << "\n";
        }
        if(m.size() == 2){
            for(int i = 0; i < c[mid].size(); i++){
                ll hash = subt_hash(c[mid][i], mid, c);
                if(m[hash] == 1){
                    vi leaf; 
                    get_leaf(c[mid][i], mid, c, leaf);
                    if(leaf.size() == 1){
                        cand.push_back(leaf[0]);
                    }
                }
            }
        }
    }
    int ans = -1;
    for(int i = 0; i < cand.size(); i++){
        if(is_valid(c, deg, cand[i])) {
            ans = cand[i];
            break;
        }
    }
    cout << (ans == -1? -1 : ans + 1) << "\n";
    
    return 0;
}