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

//Codeforces - 840B

//lets try to solve the problem without any d[i] = -1 nodes. 
//then, this is just the classic problem of toggling edges until the parities of the nodes all line up. This can be solved
//by rooting the graph at some node, generating a DFS tree, and fixing the parities bottom up. 

//it's impossible to fix the parities if the parity is initially odd in a component, but since we have these d[i] = -1 nodes,
//we can just toggle an edge connected to one of these nodes to fix the parity, then do the original solution. 

void get_component(int cur, int p, vector<vector<pii>>& c, vector<vector<pii>>& tc, vi& d, vb& v, vi& cmp) {
    assert(d[cur] != -1);
    v[cur] = true;
    cmp.push_back(cur);
    for(pii x : c[cur]) {
        if(x.first == p) continue;
        if(v[x.first]) continue;
        tc[cur].push_back(x);
        get_component(x.first, cur, c, tc, d, v, cmp);
    }
}

int get_parity(int cur, int p, vector<vector<pii>>& c, vi& d) {
    assert(d[cur] != -1);
    int ans = d[cur];
    for(pii x : c[cur]) {
        assert(x.first != p);
        ans ^= get_parity(x.first, cur, c, d);
    }
    return ans;
}

int fix_parity(int cur, int p, vector<vector<pii>>& c, vi& d, vi& ans) {
    assert(d[cur] != -1);
    int par = d[cur];
    for(pii x : c[cur]) {
        assert(x.first != p);
        int cpar = fix_parity(x.first, cur, c, d, ans);
        if(cpar) {
            ans.push_back(x.second);
            par ^= 1;
        }
    }
    return par;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vi d(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    vector<vector<pii>> c(n);
    vector<vector<pii>> tc(n);
    vi pc(n, -1);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        if(d[u] == -1 && d[v] != -1) {
            pc[v] = i;
        }
        else if(d[u] != -1 && d[v] == -1) {
            pc[u] = i;
        }
        else if(d[u] != -1 && d[v] != -1) {
            c[u].push_back({v, i});
            c[v].push_back({u, i});
        }
    }
    vector<bool> v(n, false);
    vi ans(0);
    for(int i = 0; i < n; i++) {
        if(d[i] == -1) continue;
        if(v[i]) continue;
        vi cmp;
        get_component(i, -1, c, tc, d, v, cmp);
        int par = get_parity(i, -1, tc, d);
        if(par) {
            for(int x : cmp) {
                if(pc[x] != -1) {
                    ans.push_back(pc[x]);
                    d[x] ^= 1;
                    par ^= 1;
                    break;
                }
            }
            if(par) {
                cout << "-1\n";
                return 0;
            }
        }
        par = fix_parity(i, -1, tc, d, ans);
        assert(par == 0);
    }
    cout << ans.size() << "\n";
    for(int x : ans) cout << (x + 1) << " ";
    cout << "\n";
    
    return 0;
}