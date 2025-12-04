#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

//SWERC 2020 - D

//we can visit exactly 1 interesting road each jog. The lower bound on jog length also
//doesn't matter as we can just turn around as much as we want until we hit it. 

//So this problem reduces to finding out how many unique roads we can visit given the
//maximum jog length, and that is just dijkstra 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    int L, U;
    cin >> L >> U;
    vector<vector<pair<int, int>>> c(n);
    for(int i = 0; i < m; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        c[u].push_back({v, l});
        c[v].push_back({u, l});
    }
    priority_queue<pair<int, int>> q;   //{-dist, ind}
    vector<int> d(n, 1e9);
    d[0] = 0;
    q.push({0, 0});
    while(q.size() != 0) {
        int cur = q.top().second;
        int cdist = -q.top().first;
        q.pop();
        if(cdist != d[cur]) continue;
        for(pair<int, int> x : c[cur]) {
            int ndist = cdist + x.second;
            if(ndist < d[x.first]) {
                d[x.first] = ndist;
                q.push({-ndist, x.first});
            }
        }
    }
    set<pair<int, int>> s;
    for(int i = 0; i < n; i++) {
        if(d[i] * 2 >= U) continue;
        for(pair<int, int> x : c[i]) {
            s.insert({min(x.first, i), max(x.first, i)});
        }
    }
    cout << s.size() << "\n";

    return 0;
}
