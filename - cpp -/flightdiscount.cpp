#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1195

//in order to enforce that only one discount is used, for each node, we can have two states, one where
//the discount hasn't been used, and one where the discount has been used. 

//then, for each edge, draw three edges; two full weight edges where you don't use the discount, and one half weight
//edge going from not used, to used, where you do use the discount. 

ll dijkstra(vector<vector<pair<int, ll>>> c, int start, int end) {
    int n = c.size();
    vector<ll> dist(n, -1);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 1;
    while(q.size() != 0){
        int cur = q.top().second;
        ll curDist = -q.top().first;
        q.pop();
        if(dist[cur] <= curDist) {
            continue;
        }
        dist[cur] = curDist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            ll nextDist = curDist + c[cur][i].second;
            if(dist[next] == -1 || dist[next] > nextDist) {
                if(dist[next] == -1){
                    dist[next] = nextDist + 1;
                }
                q.push({-nextDist, next});
            }
        }
    }
    return dist[end];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> c(n * 2, vector<pair<int, ll>>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        ll cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        c[a].push_back({b, cost});
        c[a].push_back({b + n, cost / 2});
        c[a + n].push_back({b + n, cost});
    }
    ll ans = dijkstra(c, 0, n * 2 - 1);
    cout << ans << "\n";
    
    return 0;
}
