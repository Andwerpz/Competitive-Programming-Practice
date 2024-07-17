#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void _dijkstra(vector<vector<pair<int, ll>>>& c, int start, vector<ll>& dist) {
    int n = c.size();
    vector<bool> v(n, false);
    dist = vector<ll>(n, 1e18);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 0;
    while(q.size() != 0){
        int cur = q.top().second;
        q.pop();
        if(v[cur]) {
            continue;
        }
        v[cur] = true;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll cost = c[cur][i].second;
            if(dist[next] > dist[cur] + cost) {
                dist[next] = dist[cur] + cost;
                q.push({-dist[next], next});    
            }
        }
    }
}

//note: untested as of 7/17/2024
void _dijkstra(vector<vector<pair<int, ll>>>& c, vector<int> start, vector<ll>& dist, vector<int>& prev) {
    int n = c.size();
    dist = vector<ll>(n, 1e18);
    prev = vector<int>(n, -1);
    vector<bool> v(n, false);
    priority_queue<pair<ll, pair<int, int>>> q;
    for(int i = 0; i < start.size(); i++){
        q.push({0, {start[i], -1}});
        dist[start[i]] = 0;
    }
    while(q.size() != 0){
        int _prev = q.top().second.second;
        int cur = q.top().second.first;
        q.pop();
        if(v[cur]) {
            continue;
        }
        v[cur] = true;
        prev[cur] = _prev;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll nextDist = dist[cur] + c[cur][i].second;
            if(dist[next] < nextDist) {
                dist[next] = nextDist;
                q.push({-nextDist, {next, cur}});
            }
        }
    }
}

ll dijkstra(vector<vector<pair<int, ll>>>& c, int start, int end) {
    int n = c.size();
    vector<ll> dist; vector<int> prev;
    _dijkstra(c, {start}, dist, prev);
    return dist[end];
}

vector<int> dijkstra_path(vector<vector<pair<int, ll>>>& c, int start, int end) {
    int n = c.size();
    vector<ll> dist; vector<int> prev;
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


