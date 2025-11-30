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

//N = 0
//E = 1
//S = 2
//W = 3

pii add(pii a, pii b) {
    return {a.first + b.first, a.second + b.second};
}

pii sub(pii a, pii b) {
    return {a.first - b.first, a.second - b.second};
}

int dir(pii a) {
    if(a.first < 0 && a.second == 0) return 3;
    else if(a.first == 0 && a.second > 0) return 0;
    else if(a.first > 0 && a.second == 0) return 1;
    else if(a.first == 0 && a.second < 0) return 2;
    assert(false);
    return -1;
}

int ndir(int cur, int curd, vector<vector<pii>>& c) {
    vi posl;
    for(int i = -1; i <= 1; i++) {
        int dir = (4 + curd + i) % 4;
        if(c[cur][dir].second > 0) posl.push_back(dir);
    }
    if(posl.size() == 0) return -1;
    if(posl.size() == 1) return posl[0];
    if(posl.size() == 2) return posl[0];
    if(posl.size() == 3) return posl[1];
    assert(false);    
    return -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    vector<vector<pii>> c(n, vector<pii>(4, {-1, -1})); //{next, value}
    for(int i = 0; i < m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u --, v --;
        int uvd = dir(sub(a[v], a[u]));
        int vud = dir(sub(a[u], a[v]));
        c[u][uvd] = {v, k};
        c[v][vud] = {u, k};
    }
    int cur, curd;  //{pos, incoming dir}
    {
        int s;
        string d;
        cin >> s >> d;
        cur = s - 1;
        if(d == "N") curd = 0;
        else if(d == "E") curd = 1;
        else if(d == "S") curd = 2;
        else if(d == "W") curd = 3;
        else assert(false);

        int next = c[cur][curd].first;
        c[cur][curd].second --;
        c[next][curd ^ 2].second --;
        cur = next;
    }
    while(true) {
        set<pii> v;         //{pos, outgoing dir}
        vector<pii> path;   //{pos, outgoing dir}
        vector<pii> cycle;  //{pos, outgoing dir}
        while(true) {
            int nd = ndir(cur, curd, c);
            if(nd == -1) goto done;
            if(v.count({cur, nd})) {
                //find path cycle
                int csind = -1;
                for(int i = 0; i < path.size(); i++) {
                    if(path[i].first == cur && path[i].second == nd) csind = i;
                }
                assert(csind != -1);
                for(int i = csind; i < path.size(); i++) {
                    cycle.push_back(path[i]);
                }
                break;
            }
            v.insert({cur, nd});
            path.push_back({cur, nd});
            int next = c[cur][nd].first;
            assert(c[cur][nd].second != 0);
            assert(next != -1);
            assert(c[next][nd ^ 2].first == cur);
            c[cur][nd].second --;
            c[next][nd ^ 2].second --;
            cur = next;
            curd = nd;
        }
        //have a path cycle, find first minimum, repeat cycle that many times
        int minval = 1e9;
        int minpos = -1;
        for(int i = 0; i < cycle.size(); i++) {
            int pos = cycle[i].first;
            int out = cycle[i].second;
            if(c[pos][out].second < minval) {
                minval = c[pos][out].second;
                minpos = i;
            }
        }
        assert(minval >= 0);
        assert(minpos != -1);
        //traverse cycle
        for(int i = 0; i < cycle.size(); i++) {
            int pos = cycle[i].first;
            int out = cycle[i].second;
            int npos = c[pos][out].first;
            assert(npos != -1);
            assert(c[pos][out].second >= minval);
            // if(i < minpos) assert(c[pos][out].second > minval);
            c[pos][out].second -= minval;
            c[npos][out ^ 2].second -= minval;
            if(i < minpos) {
                c[pos][out].second -= 1;
                c[npos][out ^ 2].second -= 1;
            }
            // assert(c[pos][out].second >= 0);
            // assert(c[npos][out ^ 2].second >= 0);
            // assert(c[pos][out].second == c[npos][out ^ 2].second);
        }
        //update cur, curd
        cur = cycle[minpos].first;
        if(minpos == 0) {
            curd = cycle[cycle.size() - 1].second;
        }
        else {
            curd = cycle[minpos - 1].second;
        }
    }
    done: {}
    // cout << (cur + 1) << "\n";
    cout << a[cur].first << " " << a[cur].second << "\n";
    
    return 0;
}