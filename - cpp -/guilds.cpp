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

//Calgary 2022 - F

//for each node, just return the root of the tree that they're in. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int ed;
    cin >> ed;
    int n = 0;
    vvi c(0);
    map<string, int> idm;
    map<int, string> ridm;
    vb is_root(0);
    set<int> oset;
    vi ord(0);
    for(int i = 0; i < ed; i++){
        string un, vn;
        cin >> un >> vn;
        if(!idm.count(un)) {
            idm[un] = n;
            ridm[n] = un;
            n ++;
            c.push_back({});
            is_root.push_back(true);
        }
        if(!idm.count(vn)) {
            idm[vn] = n;
            ridm[n] = vn;
            n ++;
            c.push_back({});
            is_root.push_back(true);
        }
        int u = idm[un];
        int v = idm[vn];
        c[v].push_back(u);
        if(!oset.count(u)) {
            ord.push_back(u);
            oset.insert(u);
        }
        is_root[u] = false;
    }
    vi ans(n, -1);
    for(int i = 0; i < n; i++){
        if(!is_root[i]) {
            continue;
        }
        queue<int> q;
        q.push(i);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            ans[cur] = i;
            for(int j = 0; j < c[cur].size(); j++) {
                int next = c[cur][j];
                q.push(next);
            }
        }
    }
    for(int i = 0; i < ord.size(); i++){
        cout << ridm[ord[i]] << " " << ridm[ans[ord[i]]] << "\n";
    }
    
    return 0;
}