#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1336A

//initially, set all the cities to tourism. Then, just greedily take the cities which will increase your score the most.
//i have no idea why this works

void calc_p(int cur, int _p, vector<int>& p, vector<int>& dist, vector<vector<int>>& c){
    p[cur] = _p;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == _p) {
            continue;
        }
        dist[next] = dist[cur] + 1;
        calc_p(next, cur, p, dist, c);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vector<int> p(n, 0), dist(n, 0);
    dist[0] = 0;
    calc_p(0, -1, p, dist, c);
    vector<int> indeg(n, 0), nr_child(n, 0);
    for(int i = 1; i < n; i++) {
        indeg[p[i]] ++;
    }
    priority_queue<pair<int, int>> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0){
            // cout << "LEAF : " << i << endl;
            q.push({dist[i], i});
        }
    }
    ll ans = 0;
    for(int i = 0; i < k; i++){
        // cout << "QSIZE : " << q.size() << "\n";
        int cur = q.top().second;
        q.pop();
        ans += dist[cur];
        ans -= nr_child[cur];
        if(cur == 0){
            continue;
        }
        // cout << "CUR : " << cur << " " << dist[cur] << " " << nr_child[cur] << "\n";
        nr_child[p[cur]] += nr_child[cur] + 1;
        indeg[p[cur]] --;
        if(indeg[p[cur]] == 0) {
            q.push({dist[p[cur]] - nr_child[p[cur]], p[cur]});
        }
    }
    cout << ans << "\n";
    
    return 0;
}