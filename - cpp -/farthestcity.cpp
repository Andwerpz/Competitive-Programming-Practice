#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<bool> vb;

// ICPC PACNW 2025 - D

const int N = 3 * 1e5 + 100;
vector<vector<pair<ll, ll>>> c(N);
vi sid(N, -1);
vl sd(N, 0);
vl su(N, 0);
vb is_cyc(N, false);

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
        pll cans = dfs3(nx, cur, cdist + x.second, d);
        ans = max(ans, cans);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // ifstream in("--in--.txt");
    // streambuf *cinbuf = cin.rdbuf(); //save old buf
    // cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    // ofstream out("--out2--.txt");
    // streambuf *coutbuf = cout.rdbuf(); //save old buf
    // cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a --;
        b --;
        c[a].push_back({b, d});
        c[b].push_back({a, d});
    }
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
                while(q.size() != 0 && q.back().second <= nval) q.pop_back();    //new entry is strictly better than this one
                q.push_back({ptr, nval});
            }   
            if(q.size() != 0) {
                ll nmx = q.front().second - cc_pfx[i];
                int ind = i;
                if(_ % 2) ind = cyc.size() - 1 - i;
                cyc_mx[ind] = max(cyc_mx[ind], nmx);
                // cout << "FORWARDS : " << i << " " << nmx << "\n";
            }
            while(q.size() != 0 && q.front().first == i) q.pop_front();
        }
        reverse(cyc.begin(), cyc.end());
    }
    //tree dists
    vl td(n, -1);
    {
        for(int i = 0; i < cyc.size(); i++) {
            int x = cyc[i];
            pll A = dfs3(x, -1, 0, td);
            pll B = dfs3(A.second, -1, 0, td);
            pll C = dfs3(B.second, -1, 0, td);
        }
    }
    vl ans(n, 0);
    for(int i = 0; i < n; i++) {
        assert(sid[i] != -1);
        assert(td[i] != -1);
        ans[i] = max(ans[i], cyc_mx[sid[i]] + su[i]);
        ans[i] = max(ans[i], td[i]);
    }
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}