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

//2022-2023 Winter Petrozavodsk Camp Day 4 - B

//first, root the tree. Then, if a node is in S, connect it to its parent. This will produce
//all the connected components. 

//To keep track of the answer, we can use DSU with rollback

struct DSU {
    int N;
    vector<int> dsu, sz;
    vector<int> s_dsu, s_sz, mdfy;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        mdfy.push_back(a);
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        if(sz[rb] > sz[ra]) swap(ra, rb);
        mdfy.push_back(ra);
        mdfy.push_back(rb);
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }

    void save() {
        s_dsu = dsu, s_sz = sz;
        mdfy.clear();
    }

    void rollback() {
        for(int x : mdfy) {
            dsu[x] = s_dsu[x];
            sz[x] = s_sz[x];
        }
        mdfy.clear();
    }
};

void dfs(int cur, int par, vi& p, vvi& c) {
    p[cur] = par;
    for(int x : c[cur]) if(x != par) dfs(x, cur, p, c);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    DSU dsu(n);
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --, b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    dsu.save();
    vi p(n, -1);
    dfs(0, -1, p, c);
    int q;
    cin >> q;
    vb in(n, false);
    while(q--){
        int k;
        cin >> k;
        ll ans = 0;
        vi s(k);
        for(int i = 0; i < k; i++) {
            cin >> s[i];
            s[i] --;
            in[s[i]] = true;
        }
        for(int i = 0; i < k; i++){
            if(p[s[i]] != -1 && in[p[s[i]]]) {
                dsu.unify(s[i], p[s[i]]);
            }
        }
        set<int> vc;
        for(int i = 0; i < k; i++){
            int ri = dsu.find(s[i]);
            if(!vc.count(ri)) {
                ans += (ll) dsu.sz[ri] * (ll) (dsu.sz[ri] - 1) / 2;
                vc.insert(ri);
            }
        }
        cout << ans << "\n";
        for(int i = 0; i < k; i++) in[s[i]] = false;
        dsu.rollback();
    }
    
    return 0;
}