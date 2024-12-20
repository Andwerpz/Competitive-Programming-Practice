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

//2024-2025 ICPC NERC - D

//The operations must be in this order: 
// - unset false
// - set true
// - set false
// - unset true
// - unset false

//we can just do a toposort to greedily grab as many of these operations in each phase as possible. 
//afterwards, we just need to do a few checks to make sure that the operation orders are in fact possible

//checks such as
// - can only do a set false after a set true
// - can only do exactly 1 set true or unset true operation. 
// - if we don't have a set true (or unset true), then can't do any more operations afterwards. 

const int USET_FALSE = 0;
const int SET_FALSE = 1;
const int USET_TRUE = 2;
const int SET_TRUE = 3;

int do_topo(int n, vvi& c, vi& indeg, vb& v, vi& t, int tgt, vi& ord){
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(!v[i] && t[i] == tgt && indeg[i] == 0){
            q.push(i);
            v[i] = true;
        }
    }
    int ans = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        ord.push_back(cur);
        ans ++;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            indeg[next] --;
            if(indeg[next] != 0) continue;
            if(v[next]) continue;
            if(t[next] != tgt) continue;
            v[next] = true;
            q.push(next);
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi t(n, 0);
    for(int i = 0; i < n; i++){
        string s1, s2;
        cin >> s1 >> s2;
        t[i] += s1 == "set"? 1 : 0;
        t[i] += s2 == "true"? 2 : 0;
    }
    int m;
    cin >> m;
    vvi c(n);
    vi indeg(n, 0);
    vb v(n, false);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        indeg[v] ++;
    }
    vi ord;
    int a_cnt = do_topo(n, c, indeg, v, t, USET_FALSE, ord);
    int b_cnt = do_topo(n, c, indeg, v, t, SET_TRUE, ord);
    int c_cnt = do_topo(n, c, indeg, v, t, SET_FALSE, ord);
    int d_cnt = do_topo(n, c, indeg, v, t, USET_TRUE, ord);
    int e_cnt = do_topo(n, c, indeg, v, t, USET_FALSE, ord);
    bool ans = true;
    if(a_cnt + b_cnt + c_cnt + d_cnt + e_cnt != n) ans = false;
    if(b_cnt > 1 || d_cnt > 1) ans = false;
    if(b_cnt == 0 && c_cnt + d_cnt + e_cnt != 0) ans = false;
    if(d_cnt == 0 && e_cnt != 0) ans = false;
    if(ans) {
        for(int i = 0; i < n; i++){
            cout << ord[i] + 1 << " ";
        }
        cout << "\n";
    }
    else {
        cout << "-1\n";
    }
    
    return 0;
}