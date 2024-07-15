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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1004E

//first, the path that we choose should always be on the diameter of the tree. 
//next, notice that if there are multiple diameters to choose from, then it doesn't actually matter which diameter
//we choose, as in that case the answer is always going to be the length of diameter / 2. 

//otherwise, we need to consider where we place our path on the diameter. Actually, the only distance
//we can minimize is the distance from the path nodes to the ends of the diameter, so we can just try 
//all possible placements in linear time using a 2 pointer approach. 

void _find_diameter_dfs(vector<vector<pair<int, ll>>>& c, vector<ll>& dist, int start) {
    int n = c.size();
    dist = vector<ll>(n, 1e18);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    while(q.size() != 0){
        ll cdist = -q.top().first;
        int cur = q.top().second;
        q.pop();
        if(cdist >= dist[cur]) {
            continue;
        }
        dist[cur] = cdist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll ndist = c[cur][i].second + cdist;
            q.push({-ndist, next});
        }
    }
}

pair<ll, pair<int, int>> find_diameter(vector<vector<pair<int, ll>>>& c){
    vector<ll> dist;
    _find_diameter_dfs(c, dist, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, dist, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    int out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}

pair<ll, pair<int, int>> find_diameter(vector<vector<int>>& c) {
    vector<vector<pair<int, ll>>> _c(c.size());
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j];
            _c[u].push_back({v, 1});
        }
    }
    return find_diameter(_c);
}

void dijkstra_info(vector<vector<pair<int, ll>>>& c, vector<int> start, vector<ll>& dist, vector<int>& prev) {
    int n = c.size();
    fill(dist.begin(), dist.end(), 1e18);
    fill(prev.begin(), prev.end(), -1);
    priority_queue<pair<ll, pair<int, int>>> q;
    for(int i = 0; i < start.size(); i++){
        q.push({0, {start[i], -1}});
    }
    while(q.size() != 0){
        int _prev = q.top().second.second;
        int cur = q.top().second.first;
        ll curDist = -q.top().first;
        q.pop();
        if(dist[cur] < curDist) {
            continue;
        }
        prev[cur] = _prev;
        dist[cur] = curDist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll nextDist = curDist + c[cur][i].second;
            q.push({-nextDist, {next, cur}});
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, ll>>> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v, d;
        cin >> u >> v >> d;
        u --;
        v --;
        c[u].push_back({v, d});
        c[v].push_back({u, d});
    }
    pii ends = find_diameter(c).second;
    // cout << "ENDS  : " << ends.first << " " << ends.second << "\n";
    vl dist(n); vi prev(n);
    dijkstra_info(c, {ends.first}, dist, prev);
    int ptr = ends.second;
    vi path(0);
    while(prev[ptr] != -1){
        path.push_back(ptr);
        ptr = prev[ptr];
    }
    path.push_back(ptr);
    vl w(0);
    for(int i = 0; i < path.size() - 1; i++){
        int u = path[i];
        int v = path[i + 1];
        for(int j = 0; j < c[u].size(); j++){
            if(c[u][j].first == v){
                w.push_back(c[u][j].second);
                break;
            }
        }
    }
    // cout << "PATH SIZE: " << path.size() << "\n";
    ll ans = 1e18;
    vi start(0);
    {
        k = min(k, (int) path.size());
        k --;
        vl pfx(w.size() + 1, 0), sfx(w.size() + 1, 0);
        for(int i = 1; i <= w.size(); i++){
            pfx[i] = pfx[i - 1] + w[i - 1];
        }
        for(int i = w.size() - 1; i >= 0; i--){
            sfx[i] = sfx[i + 1] + w[i];
        }
        int min_start = 0;
        for(int i = 0; i + k <= w.size(); i++){
            ll cans = max(pfx[i], sfx[i + k]);
            if(cans < ans) {
                ans = cans;
                min_start = i;
            }
        }
        for(int i = 0; i <= k; i++){
            // cout << "PATH : " << path[min_start + i] << "\n";
            start.push_back(path[min_start + i]);
            dist[path[min_start + i]] = 0;
        }
    }
    dijkstra_info(c, start, dist, prev);
    for(int i = 0; i < n; i++){
        ans = max(ans, dist[i]);
    }
    cout << ans << "\n";
    
    return 0;
}