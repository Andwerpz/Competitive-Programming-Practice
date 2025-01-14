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

//AtCoder - ARC95F

//First, let's identify what sort of trees we can generate using the given process. Consider starting with permutation 
//of size 1 : [1], and then progressively adding on the next largest element. The next element will always connect to the last
//element in the previous permutation, as all the elements are less than the element just added. Therefore, the
//only trees we can make are chains with length 1 branches. 

//Note that the diameter of the chain is the main body of the chain, and the rest of the nodes should be adjacent to a node on
//the diameter. This allows us to check for a buildable tree in linear time. 

//To build the tree, we can build it node by node starting from one end of the diameter. For each node in the chain, look at
//how many non-chain nodes it's adjacent to, and create exactly that many extra nodes. To lexicographically minimize the answer,
//we must try to construct the permutation starting from both ends of the chain. 

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

vi build_ans(vvi& c, vi& p) {
    int ptr = 1;
    vi ans;
    ans.push_back(ptr ++);
    for(int i = 1; i < p.size() - 1; i++){
        int cnt = c[p[i]].size() - 1;
        for(int j = 1; j < cnt; j++){
            ans.push_back(ptr + j);
        }
        ans.push_back(ptr);
        ptr += cnt;
    }
    ans.push_back(ptr ++);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vi p = find_diameter_path(c);
    vi is_diam(n, false);
    for(int i = 0; i < p.size(); i++){
        is_diam[p[i]] = true;
    }
    //check to make sure every node is either on the diameter, or one node away from it
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        if(is_diam[i]) continue;
        bool cvalid = false;
        for(int x : c[i]) if(is_diam[x]) cvalid = true;
        if(!cvalid) is_valid = false;
    }
    if(!is_valid) {
        cout << "-1\n";
        return 0;
    }
    //build permutation
    vi ans1 = build_ans(c, p);
    reverse(p.begin(), p.end());
    vi ans2 = build_ans(c, p);
    vi ans = min(ans1, ans2);
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}