#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//make sure that there are no negative weights. 
//size of dist and prev must be n. 
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


