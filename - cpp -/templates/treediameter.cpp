#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//the diameter of a tree is the maximum distance between any two nodes of the tree. 

//some diameter facts. Define A and B as endpoints of a diameter on the tree
// - If you add a new node X to the tree, then the diameter of the new tree has to be one of dist(A, B), 
//   dist(A, X), or dist(B, X). 
// - for any node in the tree X, the maximum distance from X to any other node in the tree has to be one
//   of dist(A, X) or dist(B, X). 
// - If we remove the edges on the path A -> B, we get a rooted forest. The height of each component is
//   at most the distance from the root to the closest end of the diameter. 
// - There exists a vertex such that all diameters of the tree pass through that vertex

// -- WEIGHTS ON EDGES --
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
}

// -- WEIGHTS ON NODES --
void _find_diameter_dfs(vector<vector<int>>& c, vector<ll>& a, vector<ll>& dist, int start) {
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

pair<ll, pair<int, int>> find_diameter(vector<vector<int>>& c, vector<ll>& a){
    vector<ll> dist;
    _find_diameter_dfs(c, a, dist, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, a, dist, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    ll out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}