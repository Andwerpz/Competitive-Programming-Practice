#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//2025 ICPC Shenyang Regional - F

//if there is no direct edge between x and y, then you can just direct all edges towards
//x and y and it's impossible for them to move at all. 

//otherwise, there must exist some edge x -> y

//if x -> y is not a bridge, then there exists some cycle that contains x -> y. Find a minimal
//cycle that contains x -> y, and direct any edge not on the cycle towards nodes on the cycle.
//since the cycle is minimal, there should not exist 'shortcuts', and they should not be able
//to leave the cycle. 

//otherwise, x -> y is a bridge. We need to find some path from x to a cycle, only using
//bridges. Then, just direct all edges towards the cycle, much the same as above. 

const bool debug = true;

//find a minimal cycle containing the edge x, y
//returns empty array if can't be found
vi find_minimal_cycle(int n, vvi& c, int x, int y) {
    vi d(n, 1e9), pv(n, -1);
    d[x] = 0;
    queue<int> q;
    q.push(x);
    while(q.size() != 0) {
        int cur = q.front();
        q.pop();
        for(int i = 0; i < n; i++) {
            if(!c[cur][i] || d[i] != 1e9) continue;
            if(cur == x && i == y) continue;    //remove edge x -> y
            d[i] = d[cur] + 1;
            pv[i] = cur;
            q.push(i);
        }
    }
    if(pv[y] != -1) {
        //found cycle
        vi cyc(0);
        int ptr = y;
        while(ptr != -1) {
            cyc.push_back(ptr);
            ptr = pv[ptr];
        }
        return cyc;
    }
    return {};
}

//if edge (u, v) is a bridge, then the returned set should contain {u, v} and {v, u}. 
set<pair<int, int>> _find_bridges(int n, vector<vector<int>>& adj) {
    vector<bool> visited;
    vector<int> tin, low;
    int timer;
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    set<pair<int, int>> ans;
    function<void(int, int)> dfs = [&visited, &tin, &low, &timer, &dfs, &adj, &ans](int v, int p) -> void {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v]) {
                    ans.insert({v, to});
                    ans.insert({to, v});
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i, -1);
    }
    return ans;
}

vvi find_bridges(int n, vvi& c) {
    vvi adj(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) if(c[i][j]) adj[i].push_back(j);
    }
    vvi ret(n, vi(n, 0));
    set<pii> s = _find_bridges(n, adj);
    for(pii x : s) {
        ret[x.first][x.second] = 1;
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--){
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        x --, y --;
        vvi c(n, vi(n, 0));
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u --, v --;
            assert(u != v);
            c[u][v] = 1;
            c[v][u] = 1;
        }
        if(!c[x][y]) {
            //just direct all edges towards x and y
            cout << "Yes\n";
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    if(!c[i][j]) continue;
                    if(i == x || i == y) cout << (j + 1) << " " << (i + 1) << "\n";
                    else cout << (i + 1) << " " << (j + 1) << "\n";
                }
            }
            continue;
        }
        //there is a direct connection between x and y
        //need to find a path to a cycle from x or y
        //if graph is tree, there is no cycle
        assert(m >= n - 1);
        if(m == n - 1) {
            cout << "No\n";
            continue;
        }
        //otherwise, there always should be a cycle
        //find minimal cycle containing edge x -> y
        {
            vi cyc = find_minimal_cycle(n, c, x, y);
            if(cyc.size() != 0){
                //found cycle
                vector<bool> onc(n, false);
                for(int cx : cyc) onc[cx] = true;
                cout << "Yes\n";
                int cnt = 0;
                for(int i = 0; i < cyc.size(); i++) {
                    int u = cyc[i], v = cyc[(i + 1) % cyc.size()];
                    cout << (u + 1) << " " << (v + 1) << "\n";
                    cnt ++;
                }
                for(int i = 0; i < n; i++) {
                    for(int j = i + 1; j < n; j++) {
                        if(!c[i][j]) continue;
                        if(onc[i] && onc[j]) continue;
                        if(onc[i]) cout << (j + 1) << " " << (i + 1) << "\n";
                        else cout << (i + 1) << " " << (j + 1) << "\n";
                        cnt ++;
                    }
                }
                assert(cnt == m);
                continue;
            }
        }
        //find minimal cycle in general
        //want to find path along bridge edges to this cycle
        {
            vvi bc = find_bridges(n, c);
            assert(bc[x][y]);
            //mark all nodes that belong to a doubly connected component of size >= 3
            vi cmpid(n, -1);
            {
                vi v(n, false);
                for(int i = 0; i < n; i++) {
                    if(v[i]) continue;
                    queue<int> q;
                    vi cmp;
                    q.push(i);
                    v[i] = true;
                    while(q.size() != 0){
                        int cur = q.front();
                        q.pop();
                        cmp.push_back(cur);
                        for(int j = 0; j < n; j++) {
                            if(!c[cur][j] || bc[cur][j]) continue;
                            if(v[j]) continue;
                            v[j] = true;
                            q.push(j);
                        }
                    }
                    assert(cmp.size() != 2);
                    if(cmp.size() >= 3) {
                        for(int cx : cmp) cmpid[cx] = i;
                    }
                }
            }
            //find path from x or y along bridges to a doubly connected component 
            vi path;
            {
                vi d(n, 1e9), pv(n, -1);
                queue<int> q;
                for(int i = 0; i < n; i++) {
                    if(cmpid[i] != -1) {
                        d[i] = 0;
                        q.push(i);
                    }
                }
                while(q.size() != 0){
                    int cur = q.front();
                    q.pop();
                    for(int i = 0; i < n; i++) {
                        if(!c[cur][i] || !bc[cur][i]) continue;
                        if(d[i] != 1e9) continue;
                        d[i] = d[cur] + 1;
                        pv[i] = cur;
                        q.push(i);
                    }
                }
                if(d[x] > d[y]) swap(x, y);
                assert(d[x] != 1e9);
                int ptr = x;
                path.push_back(y);
                while(ptr != -1) {
                    path.push_back(ptr);
                    ptr = pv[ptr];
                }
            }
            //find cycle in doubly connected component
            vi cyc;
            {
                int u = path[path.size() - 1];
                int v = -1;
                assert(cmpid[u] != -1);
                for(int i = 0; i < n; i++) {
                    if(c[u][i] && cmpid[u] == cmpid[i]) {
                        v = i;
                        break;
                    }
                }
                cyc = find_minimal_cycle(n, c, u, v);
            }
            //print ans
            vector<bool> onp(n, false);
            for(int px : path) onp[px] = 1;
            for(int cx : cyc) onp[cx] = 1;
            cout << "Yes\n";
            for(int i = 0; i < path.size() - 1; i++) {
                int u = path[i], v = path[i + 1];
                cout << (u + 1) << " " << (v + 1) << "\n";
            }
            for(int i = 0; i < cyc.size(); i++) {
                int u = cyc[i], v = cyc[(i + 1) % cyc.size()];
                cout << (u + 1) << " " << (v + 1) << "\n";
            }
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    if(!c[i][j]) continue;
                    if(onp[i] && onp[j]) continue;
                    if(onp[i]) cout << (j + 1) << " " << (i + 1) << "\n";
                    else cout << (i + 1) << " " << (j + 1) << "\n";
                }
            }
        }
    }

    return 0;
}