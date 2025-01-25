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

//Codeforces - 1651E

//we can compute the sum over all (L, R) for each (l, r) in amortized O(1) time. 

//

struct DSU {
    int N;
    vector<int> dsu, sz;
    vi l, r;
    vl sub;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        l = vi(n), r = vi(n);
        sub = vl(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            l[i] = i, r[i] = i + 1;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
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
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        l[ra] = min(l[ra], l[rb]);
        r[ra] = max(r[ra], r[rb]);
        sub[ra] = (ll) (l[ra] + 1) * (ll) (N - r[ra] + 1);
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> c(n, {-1, -1});
    for(int i = 0; i < n * 2; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        v -= n;
        if(c[u][0] == -1) c[u][0] = v;
        else c[u][1] = v;
    }
    vl scnt(n + 1, 0);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j <= n; j++) scnt[i] ++, scnt[j] --;
    }
    for(int i = 1; i <= n; i++) scnt[i] += scnt[i - 1];
    ll ans = 0;
    for(int i = 0; i < n; i++){
        DSU dsu(n);
        ll cans = 0;
        vi deg(n, 0);
        for(int j = i; j < n; j++){
            int u = c[j][0], v = c[j][1];
            if(deg[u] == 0) cans += scnt[u];
            if(deg[v] == 0) cans += scnt[v];
            deg[u] ++, deg[v] ++;
            int ru = dsu.find(u), rv = dsu.find(v);
            if(ru == rv) {
                cans += dsu.sub[ru];
            }
            else {
                cans += dsu.sub[ru] + dsu.sub[rv];
                dsu.unify(u, v);
                cans -= dsu.sub[dsu.find(u)];
            }
            ans += cans;
        }
    }
    cout << ans << "\n";
    
    return 0;
}