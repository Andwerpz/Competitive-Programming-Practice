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

//Codeforces - 1842F

//first, observe that any optimal placement of black nodes will always have them form a connected component. 
//so the rough idea is for each k, we can kinda iterate through all possible placements of black nodes such that 
//they form a connected component. 

//however, for a given k, there may be too many different arrangements of black nodes to test, so the second observation
//is that all the black nodes want to 'clump together' as much as possible. More formally, if we fix the centroid of the 
//black nodes, then the black nodes should be greedily placed as close as possible to the centroid. 

//so our solution is: for every centroid, do a bfs and place the black nodes with increasing distance from the centroid. 
//The value for some placement is k * (n - 1) - sum(dist) * 2, where sum(dist) is the sum of distances of black nodes from
//the centroid black node. 

//for each k, we'll take the minimum answer out of all centroids. Note that the answer that we compute for some centroids will
//be lower than the actual answer, but that's ok as the optimal answer will always have a black node centroid that follows
//the greedy principle above. 

void solve(int cent, vvi& c, vl& ans) {
    int n = c.size();
    vb v(n, false);
    v[cent] = true;
    queue<pii> q;   //{node, dist}
    for(int x : c[cent]) q.push({x, 1});
    ll subt = 0;
    for(ll k = 2; k <= n; k++){
        int cur = q.front().first;
        int dist = q.front().second;
        q.pop();
        subt += dist * 2;
        v[cur] = true;
        for(int x : c[cur]) if(!v[x]) q.push({x, dist + 1});
        ll cans = k * (n - 1) - subt;
        ans[k] = max(ans[k], cans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vl ans(n + 1, 0);
    ans[1] = n - 1;
    for(int i = 0; i < n; i++){
        solve(i, c, ans);
    }
    for(ll x : ans) cout << x << " ";
    cout << "\n";
    
    return 0;
}