#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//CSES - 1131

void _find_diameter_dfs(vector<vector<int>>& c, vector<int>& dist, int start) {
    int n = c.size();
    dist = vector<int>(n, 1e9);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(dist[cur] + 1 < dist[next]) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }
}

pair<int, pair<int, int>> _find_diameter(vector<vector<int>>& c) {
    vector<int> dist;
    _find_diameter_dfs(c, dist, 0);
    int out_a = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    _find_diameter_dfs(c, dist, out_a);
    int out_b = distance(dist.begin(), max_element(dist.begin(), dist.end()));
    int out_dist = dist[out_b];
    return {out_dist, {out_a, out_b}};
}

int find_diameter(vector<vector<int>>& c) {
    return _find_diameter(c).first;
}

pair<int, int> find_diameter_ends(vector<vector<int>>& c) {
    return _find_diameter(c).second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    cout << find_diameter(c) << "\n";
    
    return 0;
}