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
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//AtCoder - AGC56C

//let v[i] = (nr 0s used in the first i elements) - (nr 1s used in the first i elements)
//note that from v[i] we can derive the string, and that lexicographically maximizing v[i] is equivalent
//to minimizing the string. 

//there are two rules we must follow when constructing v, 
//1. |v[i] - v[i + 1]| = 1
//2. v[l_i] = v[r_i]

//to construct v, we can treat it as a shortest paths problem: create some sort of graph that represents
//all the constraints and then find the shortest paths to all nodes. 

//we can construct the graph like so:
//graph will have n + 1 nodes, one starting node and one for each index. 
// - for all i, put an edge from node i to i + 1 of weight 1
// - for each l, r, constraint, put an edge (l_i, r_i) of weight 0. 

//somehow finding the shortest path also gives you a lexicographically maximized v. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> c(n + 1);
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        l --;
        c[l].push_back({r, 0});
        c[r].push_back({l, 0});
    }
    for(int i = 0; i < n; i++){
        c[i].push_back({i + 1, 1});
        c[i + 1].push_back({i, 1});
    }
    vi d(n + 1, 1e9);
    d[0] = 0;
    priority_queue<pii> q;
    q.push({0, 0});
    while(q.size() != 0){
        int cur = q.top().second;
        int cdist = -q.top().first;
        q.pop();
        if(cdist != d[cur]) continue;
        for(pii next : c[cur]) {
            int ndist = cdist + next.second;
            if(ndist < d[next.first]) {
                d[next.first] = ndist;
                q.push({-ndist, next.first});
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << (d[i] > d[i + 1]);
    }
    cout << "\n";
    
    return 0;
}