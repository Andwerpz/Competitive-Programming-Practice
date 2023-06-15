#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//make sure that there are no negative weights. 
//returns the minimum distance, or -1 if there is no path
ll dijkstra(vector<vector<pair<int, ll>>>& c, int start, int end) {
    int n = c.size();
    vector<ll> dist(n, -1);
    vector<int> prev(n, -1);
    vector<bool> v(n, false);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 0;
    v[start] = true;
    while(q.size() != 0){
        int cur = q.top().second;
        ll curDist = -q.top().first;
        q.pop();
        if(dist[cur] < curDist) {
            continue;
        }
        dist[cur] = curDist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll nextDist = curDist + c[cur][i].second;
            if(!v[next] || dist[next] > nextDist) {
                v[next] = true;
                dist[next] = nextDist;
                prev[next] = cur;
                q.push({-nextDist, next});
            }
        }
    }
}

//make sure that there are no negative weights. 
//size of dist and prev must be n. 
void dijkstra_info(vector<vector<pair<int, ll>>>& c, int start, vector<ll>& dist, vector<int>& prev, vector<bool>& v) {
    int n = c.size();
    fill(dist.begin(), dist.end(), -1);
    fill(prev.begin(), prev.end(), -1);
    fill(v.begin(), v.end(), false);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 0;
    v[start] = true;
    while(q.size() != 0){
        int cur = q.top().second;
        ll curDist = -q.top().first;
        q.pop();
        if(dist[cur] < curDist) {
            continue;
        }
        dist[cur] = curDist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll nextDist = curDist + c[cur][i].second;
            if(!v[next] || dist[next] > nextDist) {
                v[next] = true;
                dist[next] = nextDist;
                prev[next] = cur;
                q.push({-nextDist, next});
            }
        }
    }
}
