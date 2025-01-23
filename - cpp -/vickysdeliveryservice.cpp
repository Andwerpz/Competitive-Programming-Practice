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

//Codeforces - 1166F

//nice dsu problem. 

//note that rainbow paths are just paths where every two edge colors are the same. However if the path length is odd
//then the last edge can be whatever color you want. 

//Let's first solve with the restriction that the path length must be even. In this case, it's pretty obvious we can
//use dsu to maintain the connectivity of the graph when adding edges. When we add an edge of color c to (u, v), 
//we just need to check if there are any other edges of color c already connected to u. If there are, we can connect
//v directly to one of them (they should all already be connected) and likewise with u to v. 

//Now, we consider odd length rainbow paths. To check whether or not it's possible to get from u to v, we need
//to see if there is an even length path from u to v, or from u to one of v's neighbors because then the last edge
//can just be directly from the neighbor to v. 

//Naively what we can do is to just save the set of components that v is adjacent to, and see if the component u 
//belongs to is in that set. We can see that the sum of adjacent components over all nodes is bounded by the number
//of edges, but how fast is it to update the component set after adding an edge?

//If we use DSU with small to large merging, we can get it down to amortized log(n)^2. If we want to merge component
//a into b, we need to update all nodes that are adjacent to some node in a. Since each node will only be merged into
//another component at most log(n) times, and we're doing set operations (another log(n)), total time complexity comes
//out to be O(n * log(n)^2). 

int n, m, _c, q;
vector<map<int, int>> cmap;
vector<set<int>> s;
vvi c;

struct DSU {
    int N;
    vector<int> dsu, sz;
    vector<vector<int>> g;

    DSU() {}
    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        g = vvi(n);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            g[i] = {i};
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
        for(int x : g[rb]) g[ra].push_back(x);
        //for every element that is adjacent to rb, update it
        for(int x : g[rb]) {
            for(int y : c[x]) {
                if(s[y].count(rb)) s[y].erase(rb), s[y].insert(ra);
            }
        }
        return true;
    }
};

DSU dsu;

void add_edge(int u, int v, int col) {
    s[u].insert(dsu.find(v)), s[v].insert(dsu.find(u));
    c[u].push_back(v), c[v].push_back(u);
    if(cmap[u].count(col)) dsu.unify(v, cmap[u][col]);
    if(cmap[v].count(col)) dsu.unify(u, cmap[v][col]);
    cmap[u][col] = v, cmap[v][col] = u;
}

bool query(int u, int v) {
    return s[v].count(dsu.find(u)) || dsu.find(u) == dsu.find(v);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> m >> _c >> q;
    c = vvi(n);
    cmap = vector<map<int, int>>(n);
    s = vector<set<int>>(n);
    dsu = DSU(n);
    for(int i = 0; i < m; i++){
        int u, v, col;
        cin >> u >> v >> col;
        u --, v --;
        add_edge(u, v, col);
    }
    for(int i = 0; i < q; i++){
        string type;
        cin >> type;
        if(type == "?") {
            int u, v;
            cin >> u >> v;
            u --, v --;
            cout << (query(u, v)? "Yes" : "No") << "\n";
        }
        else {
            int u, v, col;
            cin >> u >> v >> col;
            u --, v --;
            add_edge(u, v, col);
        }
    }
    
    return 0;
}