#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2013 - C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, comm;
    cin >> n >> m >> comm;
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
    for(int i = 0; i < m; i++){
        int x, y, t;
        cin >> x >> y >> t;
        x --;
        y --;
        c[x].push_back({y, t});
        c[y].push_back({x, t});
    }
    vector<bool> v(n, false);
    vector<int> cap(n, 0);
    cap[0] = 1e9;
    vector<int> nr_comm(n, 0);
    for(int i = 0; i < comm; i++){
        int loc;
        cin >> loc;
        loc --;
        nr_comm[loc] ++;
    }
    vector<int> t(n, 1e9);
    t[0] = 0;
    priority_queue<pair<int, int>> q;   //{-time, node}
    q.push({0, 0});
    set<int> comm_t;
    int ans = 0;
    while(q.size() != 0){
        int time = -q.top().first;
        int cur = q.top().second;
        q.pop();
        if(time > t[cur] || v[cur]) {
            continue;
        }
        v[cur] = true;
        for(int i = 0; i < c[cur].size(); i++){
            int cost = c[cur][i].second;
            int next = c[cur][i].first;
            //update capacity
            if(cap[next] != 0){
                cap[cur] ++;
            }
            //try to visit
            if(v[next]) {
                continue;
            }
            q.push({-(time + cost), next});
            t[next] = min(t[next], time + cost);
        }
    }
    for(int i = 0; i < n; i++){
        if(nr_comm[i] != 0){
            comm_t.insert(t[i]);
        }
    }
    for(auto i = comm_t.begin(); i != comm_t.end(); i++){

    }
    cout << ans << "\n";
    
    return 0;
}
