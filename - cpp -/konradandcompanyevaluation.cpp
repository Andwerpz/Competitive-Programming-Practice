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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1210D

//first observation is that the number of dangerous triples is just the sum of indeg * outdeg over all nodes. 
//Consider we fix node i as the center of a dangerous triple. Then, we need someone to brag to i, and someone for i to 
//brag to. Then, pretty obviously, the amount of triples with i at the center is just indeg[i] * outdeg[i]. 

//now, when we revise employee i's salary, we basically just set all edges connecting to i to face away from i. 
//we can recompute the cost after switching the direction of an edge in O(1), and we can only consider edges that 
//are coming into i by keeping track of them in some sort of stack. 

//actually, no further optimizations are needed. Each query will run at worst around O(sqrt(m)) time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vl indeg(n, 0), outdeg(n, 0);
    vector<stack<int>> inid(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        if(u > v){
            swap(u, v);
        }
        indeg[u] ++;
        outdeg[v] ++;
        inid[u].push(v);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += indeg[i] * outdeg[i];
    }
    int q;
    cin >> q;
    cout << ans << "\n";
    for(int i = 0; i < q; i++){
        int cur;
        cin >> cur;
        cur --;
        ans -= indeg[cur] * outdeg[cur];
        outdeg[cur] += indeg[cur];
        indeg[cur] = 0;
        while(inid[cur].size() != 0){
            int next = inid[cur].top();
            inid[cur].pop();
            ans -= indeg[next];
            outdeg[next] --;
            ans += outdeg[next];
            indeg[next] ++;
            inid[next].push(cur);
        }
        cout << ans << "\n";
    }
    
    return 0;
}