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

//Codeforces - 2143C

//we can transform the problem a bit:

//reduce the x, y values of each edge by min(x, y). Add min(x, y) for every edge to your score. 
//now, at least one of x, y for each edge will be 0, so in order to gain this extra value,
//we want some condition either p_u > p_v or p_u <= p_v to be true. 

//draw an edge in the direction of the node that should have greater value. Observe that the resulting graph
//is always a DAG, and therefore we can always find a topological ordering for a DAG, which means there always
//exists a permutation such that we can claim all of the extra value. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vvi c(n);
        for(int i = 0; i < n - 1; i++) {
            int u, v, x, y;
            cin >> u >> v >> x >> y;
            u --, v --;
            if(x >= y) c[u].push_back(v);
            else c[v].push_back(u);
        }
        vi indeg(n, 0);
        for(int i = 0; i < n; i++) for(int x : c[i]) indeg[x] ++;
        queue<int> q;
        for(int i = 0; i < n; i++) if(indeg[i] == 0) q.push(i);
        vi p(n, -1);
        int ptr = n;
        while(q.size()) {
            int cur = q.front();
            q.pop();
            p[cur] = ptr --;
            for(int x : c[cur]) {
                indeg[x] --;
                if(indeg[x] == 0) q.push(x);
            }
        }
        for(int i = 0; i < n; i++) cout << p[i] << " ";
        cout << "\n";
    }
    
    return 0;
}