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

//Codeforces - 633F

//the problem boils down to finding the largest sum of nodes if you can only choose 2 disjoint simple paths. 

//note that there are actually only 2 cases that produce the best answer:
// - one path is the diameter, and another path is not on the diameter
// - one path is the prefix of the diameter, and one path is the suffix. They both exit the diameter to go into 
//   some adjacent subtree. 

//we can try all of these in linear time. Note that the selection of diameter actually doesn't matter. 

void _find_diameter_dfs(vector<vector<int>>& c, vl& a, vector<ll>& dist, int start) {
    int n = c.size();
    dist = vector<ll>(n, 1e18);
    vector<bool> v(n, false);
    queue<int> q;
    q.push(start);
    v[start] = true;
    dist[start] = a[start];
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            ll ndist = a[next] + dist[cur];
            if(!v[next]) {
                v[next] = true;
                dist[next] = ndist;
                q.push(next);
            }
        }
    }
}

pair<ll, pair<int, int>> find_diameter(vector<vector<int>>& c, vl& a){
    vector<ll> dist;
    _find_diameter_dfs(c, a, dist, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, a, dist, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    ll out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}

void _dijkstra(vector<vector<pair<int, ll>>>& c, vector<int> start, vector<ll>& dist, vector<int>& prev) {
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

ll dijkstra(vector<vector<pair<int, ll>>>& c, int start, int end) {
    int n = c.size();
    vector<ll> dist(n);
    vector<int> prev(n);
    _dijkstra(c, {start}, dist, prev);
    return dist[end];
}

vector<int> dijkstra_path(vector<vector<pair<int, ll>>>& c, int start, int end) {
    int n = c.size();
    vector<ll> dist(n);
    vector<int> prev(n);
    _dijkstra(c, {start}, dist, prev);
    vector<int> path(0);
    int ptr = end;
    while(prev[ptr] != -1){
        path.push_back(ptr);
        ptr = prev[ptr];
    }
    path.push_back(ptr);
    reverse(path.begin(), path.end());
    return path;
}

vector<int> dijkstra_path(vector<vector<int>>& c, int start, int end) {
    vector<vector<pair<int, ll>>> _c(c.size());
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j];
            _c[u].push_back({v, 1});
        }
    }
    return dijkstra_path(_c, start, end);
}

void dfs1(int cur, int p, vector<vi>& c, vector<pll>& subt_path, vl& a) {
    pll ans = {a[cur], a[cur]};
    vector<ll> paths(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dfs1(next, cur, c, subt_path, a);
        ans.first = max(ans.first, subt_path[next].first);
        ans.second = max(ans.second, subt_path[next].second + a[cur]);
        paths.push_back(subt_path[next].second);
    }
    sort(paths.begin(), paths.end());
    reverse(paths.begin(), paths.end());
    ll psum = a[cur];
    for(int i = 0; i < min((int) paths.size(), 2); i++){
        psum += paths[i];
    }
    ans.first = max(ans.first, psum);
    subt_path[cur] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vi> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    pii ends;
    ll d_len;
    {
        pair<ll, pii> tmp = find_diameter(c, a);
        ends = tmp.second;
        d_len = tmp.first;
    }
    vi path = dijkstra_path(c, ends.first, ends.second);
    vector<pll> subt_path(n);   //{max path in subtree, max path ending at this node}
    dfs1(ends.first, -1, c, subt_path, a);
    vb on_path(n, false);
    for(int i = 0; i < path.size(); i++){
        on_path[path[i]] = true;
    }
    ll mx_subt_path = 0;
    vl mpe(path.size(), 0);
    for(int i = 0; i < path.size(); i++){
        int cur = path[i];
        ll cmpe = 0;
        for(int j = 0; j < c[cur].size(); j++){
            int next = c[cur][j];
            if(on_path[next]) {
                continue;
            }
            cmpe = max(cmpe, subt_path[next].second);
            mx_subt_path = max(mx_subt_path, subt_path[next].first);
        }
        mpe[i] = cmpe;
    }
    ll ans = mx_subt_path + d_len;
    ll pfx = d_len;
    ll sfx = 0;
    ll m_sfx = 0;
    for(int i = path.size() - 1; i > 0; i--){
        int cur = path[i];
        pfx -= a[cur];
        sfx += a[cur];
        m_sfx = max(m_sfx, sfx + mpe[i]);
        ll cans = pfx + mpe[i - 1] + m_sfx;
        ans = max(ans, cans);
    }
    cout << ans << "\n";
    
    return 0;
}