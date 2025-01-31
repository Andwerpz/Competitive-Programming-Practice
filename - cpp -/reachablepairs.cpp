#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//USACO 2025 January Contest Gold 2

//type 0 will actually remove the node, while type 1 doesn't affect the connectivity of the graph (aside from 
//removing the node)

//so instead of removing the node and adding edges between all pairs of neighbors, we can just say that the type 1
//operation just removes any pair with that node from the count. 

//This leads to a solution working backwards. We can initially have all edges belonging to nodes removed with type 1
//already in the DSU, and add edges belonging to nodes removed with type 0 as we work to the front. 

struct DSU {
    int N;
    vector<int> dsu;
    vl sz;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<ll>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    ll get_sz(int a) {
        return sz[find(a)];
    }

    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    string s;
    cin >> s;
    map<pii, int> eid;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
        eid[{u, v}] = i + n, eid[{v, u}] = i + n;
    }
    DSU dsu(n + m);
    for(int i = 0; i < n; i++){
        if(s[i] == '0') continue;
        for(int j = 0; j < c[i].size(); j++){
            int u = i, v = c[i][j];
            dsu.unify(u, eid[{u, v}]);
        }
    }
    vl ans(n);
    ll cans = 0;
    for(int i = n - 1; i >= 0; i--){
        if(s[i] == '0') {
            for(int j = 0; j < c[i].size(); j++){
                int u = i, v = c[i][j];
                int ru = dsu.find(u), rv = dsu.find(v);
                if(ru == rv) continue;
                int e = eid[{u, v}];
                ll osz = dsu.get_sz(e);
                if(dsu.unify(u, e)) cans -= osz * (osz - 1) / 2;
            }
            cans += dsu.get_sz(i) * (dsu.get_sz(i) - 1) / 2;
        }
        cans -= dsu.get_sz(i) * (dsu.get_sz(i) - 1) / 2;
        dsu.sz[dsu.find(i)] ++;
        cans += dsu.get_sz(i) * (dsu.get_sz(i) - 1) / 2;
        // cout << "SZ : " << dsu.get_sz(i) << " " << dsu.find(i) << "\n";
        ans[i] = cans;
    }
    for(int i = 0; i < n; i++) cout << ans[i] << "\n";
    
    return 0;
}