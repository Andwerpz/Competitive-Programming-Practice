#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<bool> vb;

// ICPC PACNW 2025 - D

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

const bool debug = false;
vector<vector<pair<ll, ll>>> c;
vi sid;
vl sd;
vl su;
vb is_cyc;

bool dfs(int cur, int p, vb& v, vi& cyc) {
    v[cur] = 1;
    cyc.push_back(cur);
    for(pair<ll, ll> x : c[cur]) {
        int nx = x.first;
        if(nx == p) continue;
        if(v[nx]) {
            //found cycle
            int ind = -1;
            for(int i = 0; i < cyc.size(); i++) {
                if(cyc[i] == nx) ind = i;
            }
            assert(ind != -1);
            vi tmp;
            for(int i = ind; i < cyc.size(); i++) {
                tmp.push_back(cyc[i]);
            }
            assert(tmp.size() >= 3);
            cyc = tmp;
            return true;
        }
        if(dfs(nx, cur, v, cyc)) return true;
    }
    cyc.pop_back();
    return false;
}

void dfs2(int cur, int p, int csid) {
    assert(sid[cur] == -1);
    sid[cur] = csid;
    for(pll x : c[cur]) {
        int nx = x.first;
        if(nx == p) continue;
        if(is_cyc[nx]) continue;
        su[nx] = su[cur] + x.second;
        dfs2(nx, cur, csid);
        sd[cur] = max(sd[cur], sd[nx] + x.second);
    }
}

pll dfs3(int cur, int p, ll cdist, vl& d) {
    pll ans = {cdist, cur};
    d[cur] = max(d[cur], cdist);
    for(pll x : c[cur]) {
        int nx = x.first;
        if(nx == p) continue;
        if(sid[nx] != sid[cur]) continue;
        // cout << "DFS3 : " << cur << " " << nx << " " << x.second << endl;
        pll cans = dfs3(nx, cur, cdist + x.second, d);
        ans = max(ans, cans);
    }
    return ans;
}

vl solve(int n, vector<vector<pll>> _c) {
    assert(n == _c.size());
    c = _c;
    sid = vi(n, -1);
    sd = vl(n, 0);
    su = vl(n, 0);
    is_cyc = vb(n, false);

    vi cyc;
    vb v(n, false);
    dfs(0, -1, v, cyc);
    for(int x : cyc) is_cyc[x] = true;
    for(int i = 0; i < cyc.size(); i++) {
        int x = cyc[i];
        dfs2(x, -1, i);
    }
    vl cyc_mx(cyc.size(), 0);
    //paths containing the cycle
    for(int _ = 0; _ < 2; _++) {   
        // cout << "ITER : " << _ << "\n";
        vl cc(cyc.size(), -1);
        for(int i = 0; i < cyc.size(); i++) {
            int u = cyc[i];
            int v = cyc[(i + 1) % cyc.size()];
            for(pair<ll, ll> x : c[u]) {
                int nx = x.first;
                if(nx == v) cc[i] = x.second;
            }
            assert(cc[i] != -1);
        }  
        vl cc_pfx(cyc.size() * 3 + 1, 0);
        for(int i = 1; i <= cyc.size() * 3; i++) {
            cc_pfx[i] = cc_pfx[i - 1] + cc[(i - 1) % cyc.size()];
        }
        ll cc_tot = cc_pfx[cyc.size()];
        // cout << "CC : ";
        // for(ll x : cc) cout << x << " ";
        // cout << "\n";
        deque<pll> q;   //{ind, val}, closer to front val increases and ind decreases
        int ptr = 0;
        for(int i = 0; i < cyc.size(); i++) {
            if(ptr < i) ptr = i;
            while(true) {
                int nptr = ptr + 1;
                ll ndist = cc_pfx[nptr] - cc_pfx[i];
                if(ndist > cc_tot - ndist) break;
                ptr = nptr;
                ll nval = cc_pfx[ptr] + sd[cyc[ptr % cyc.size()]];
                // cout << "SD : " << ptr << " " << cyc[ptr % cyc.size()] << " " << sd[cyc[ptr % cyc.size()]] << "\n";
                while(q.size() != 0 && q.back().second <= nval) q.pop_back();    //new entry is strictly better than this one
                q.push_back({ptr, nval});
            }   
            if(q.size() != 0) {
                ll nmx = q.front().second - cc_pfx[i];
                int ind = i;
                if(_ % 2) ind = cyc.size() - 1 - i;
                cyc_mx[ind] = max(cyc_mx[ind], nmx);
                // cout << "UPDATE : " << i << " " << nmx << " " << q.front().second << " " << cc_pfx[i] << "\n";
            }
            while(q.size() != 0 && q.front().first == i + 1) q.pop_front();
        }
        reverse(cyc.begin(), cyc.end());
    }
    // cout << "CYC MAX : ";
    // for(int i = 0; i < cyc.size(); i++) {
    //     cout << cyc_mx[i] << " ";
    // }
    // cout << "\n";

    //tree dists
    vl td(n, -1);
    {
        for(int i = 0; i < cyc.size(); i++) {
            int x = cyc[i];
            pll A = dfs3(x, -1, 0, td);
            pll B = dfs3(A.second, -1, 0, td);
            pll C = dfs3(B.second, -1, 0, td);
        }

        // cout << "SID : ";
        // for(int i = 0; i < n; i++) cout << sid[i] << " ";
        // cout << endl;

        // cout << "TD : ";
        // for(int i = 0; i < n; i++) cout << td[i] << " ";
        // cout << endl;
    }
    vl ans(n, 0);
    for(int i = 0; i < n; i++) {
        assert(sid[i] != -1);
        assert(td[i] != -1);
        ans[i] = max(ans[i], cyc_mx[sid[i]] + su[i]);
        ans[i] = max(ans[i], td[i]);
    }
    return ans;
}

vl solve_brute(int n, vector<vector<pll>> _c) {
    assert(n == _c.size());
    c = _c;

    vl ans(n, -1);
    for(int _ = 0; _ < n; _++) {
        vl d(n, 1e18);
        d[_] = 0;
        priority_queue<pll> q;  //{-dist, ind}
        q.push({0, _});
        while(q.size() != 0) {
            int cur = q.top().second;
            ll cdist = -q.top().first;
            q.pop();
            if(d[cur] != cdist) continue;
            ans[_] = max(ans[_], d[cur]);
            for(pll x : c[cur]) {
                int nx = x.first;
                ll ndist = cdist + x.second;
                // cout << "NDIST : " << ndist << " " << nx << "\n";
                if(ndist < d[nx]) {
                    d[nx] = ndist;
                    q.push({-ndist, nx});
                }
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    srand(time(0));

    // ifstream in("--in--.txt");
    // streambuf *cinbuf = cin.rdbuf(); //save old buf
    // cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    // ofstream out("--out2--.txt");
    // streambuf *coutbuf = cout.rdbuf(); //save old buf
    // cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    if(debug) {
        int n = 10;
        ll cnt = 0;
        while(true) {
            vector<vector<pll>> c(n);
            vl w(n);
            for(int i = 0; i < n; i++) {
                w[i] = rand() % n + 1;
                // w[i] = ((ll) rand() + ((ll) rand() << 16)) % ((ll) 1e7) + 1;
            }
            if(0) {
                //generate cycle + spokes with random weights
                assert(n % 2 == 0);
                for(int i = 0; i < n / 2; i++) {
                    c[i].push_back({(i + 1) % (n / 2), w[i]});
                    c[(i + 1) % (n / 2)].push_back({i, w[i]});

                    c[i].push_back({i + (n / 2), w[i + (n / 2)]});
                    c[i + (n / 2)].push_back({i, w[i + (n / 2)]});
                }
            }
            else {
                //generate random tree with DSU, then add an edge
                DSU dsu(n);
                vector<set<int>> adj(n);
                vi p(n);
                for(int i = 0; i < n; i++) p[i] = i;
                for(int i = 0; i < n - 1; i++) {
                    int u = rand() % n;
                    random_shuffle(p.begin(), p.end());
                    for(int x : p) {
                        if(u == x) continue;
                        if(dsu.unify(u, x)) {
                            adj[u].insert(x);
                            adj[x].insert(u);

                            c[u].push_back({x, w[i]});
                            c[x].push_back({u, w[i]});
                            // cout << "EDGE : " << u << " " << x << "\n";
                            break;
                        }
                    }
                }
                while(1) {
                    int u = rand() % n;
                    int v = rand() % n;
                    if(u == v) continue;
                    if(adj[u].find(v) == adj[u].end()) {
                        c[u].push_back({v, w[n - 1]});
                        c[v].push_back({u, w[n - 1]});
                        // cout << "EXTRA : " << u << " " << v << endl;
                        break;
                    }
                }
            }
            vl ans = solve(n, c);
            vl ans_brute = solve_brute(n, c);
            if(ans != ans_brute) {
                cout << "BRUH\n";
                for(ll x : ans) cout << x << " ";
                cout << "\n";
                for(ll x : ans_brute) cout << x << " ";
                cout << "\n";
                for(ll x : w) cout << x << " ";
                cout << "\n";
                cout.flush();
                assert(0);
            }
            cnt ++;
            if(cnt % 100 == 0) cout << "GOOD : " << cnt << endl;
        }   
    }
    else {
        int n;
        cin >> n;
        vector<vector<pll>> c(n);
        for(int i = 0; i < n; i++) {
            ll a, b, d;
            cin >> a >> b >> d;
            a --;
            b --;
            c[a].push_back({b, d});
            c[b].push_back({a, d});
        }
        vl ans = solve(n, c);
        if(debug) {
            vl ans_brute = solve_brute(n, c);
            assert(ans == solve_brute(n, c));
        }
        for(ll x : ans) cout << x << " ";
        cout << "\n";
    }

    return 0;
}