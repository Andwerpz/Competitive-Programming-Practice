#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
map<pi, ll> edges;
vector<ll> candies(112345);

//ICPC World Finals 2020 Online L

//this can be boiled down to a dsu problem. 

struct DSU {
    int N;
    vector<int> dsu;
    vector<ll> vals, sums;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        vals = vector<ll> (n, 1e10);
        sums = vector<ll> (n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            sums[i] = candies[i];
        }
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    ll get_ans(int k) {
        return vals[find(k)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);

        ll new_val = min({vals[ra], vals[rb], max(-sums[ra] + edges[{a, b}], -sums[rb] + edges[{a, b}])});
        
        if(ra == rb) {
            return false;
        }
        // cerr << "a : " << ra << " b : " << rb << endl;
        // cerr << "sumsra : " << sums[ra] << " sumrb : " << sums[rb] << endl;
        sums[ra] += sums[ra];
        vals[ra] = new_val;
        dsu[rb] = ra;

        return true;
    }
};



int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, m; cin >> n >> m;

    for (int i = 0; i < n; ++i) cin >> candies[i];

    vector<vector<pair<int, ll>>> adj(n+1);

    vector<vector<ll>> vedges;

    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        a--;
        b--;
        ll c; cin >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        vedges.push_back({c, a, b});
        edges[{a, b}] = c;
        edges[{b, a}] = c;
    }

    // cerr << "hey" << endl;

    sort(vedges.rbegin(), vedges.rend());

    DSU dsu = DSU(n); 
    for (int i = 0; i < m; ++i) {
        // cerr << "i : " << i << endl;
        int a = vedges[i][1], b = vedges[i][2];
        // cerr << "a : " << a << " b : " << b << endl;
        dsu.unify(a, b); 
    }

    ll cnt = dsu.get_ans(0);

    if (cnt <= 0) {
        cout << -1 << endl;
    } else cout << cnt << endl;

    
    return 0;
}