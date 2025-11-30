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

//UIUC IPL Team Tryout 2025 - B

//observe that if you just build the MST of all the nodes, then travelling along the MST will always
//minimize the maximum distance between adjacent nodes. 
//(to see why this is, consider how exactly you're building the MST)

struct vec2 {
    ld x, y;
};

ld dist(vec2 a, vec2 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct DSU {
    int N;
    vector<int> dsu, sz;

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
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vec2> a;
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }
    //build MST
    vector<pair<ld, pii>> e;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            e.push_back({dist(a[i], a[j]), {i, j}});
        }
    }
    sort(e.begin(), e.end());
    vector<vector<pair<int, ld>>> c(n);
    DSU dsu(n);
    for(int i = 0; i < e.size(); i++){
        ld d = e[i].first;
        int u = e[i].second.first;
        int v = e[i].second.second;
        if(dsu.unify(u, v)) {
            c[u].push_back({v, d});
            c[v].push_back({u, d});
        }
    }
    //all pairs shortest paths
    vvd d(n, vd(n, 1e18));
    for(int i = 0; i < n; i++) {
        d[i][i] = 0;
        queue<int> q;
        q.push(i);
        while(q.size()) {
            int cur = q.front();
            q.pop();
            // cout << "DIST : " << i << " " << cur << " " << d[i][cur] << "\n";
            for(pair<int, ld> x : c[cur]) {
                int next = x.first;
                if(d[i][next] != 1e18) continue;
                d[i][next] = max(d[i][cur], x.second);
                q.push(next);
            }
        }
    }
    //handle queries
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        cout << fixed << setprecision(10) << d[u][v] << "\n";
    }
    
    return 0;
}