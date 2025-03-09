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

//Topcoder - 12554

//i'm pretty much just bruteforcing it here, and it takes too long. 
//there has to be a better way to do this. 

vi dr = {-1, 1, 0, 0};
vi dc = {0, 0, -1, 1};
int n;

struct UCF_MCMF {
    const ll INF = LLONG_MAX >> 2;

    struct Edge {
        int v;
        ll cap, flow, cost;
    };

    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<pair<int, int>> par;
    vector<int> in_q;
    vector<ll> dist, pi;

    UCF_MCMF(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        int idx = edges.size();
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }

    bool find_path(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(in_q.begin(), in_q.end(), 0);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        in_q[s] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = 0;

            for (int idx : adj[cur]) {
                Edge& e = edges[idx];
                int nxt = e.v;
                ll cap = e.cap, fl = e.flow, wt = e.cost;
                ll nxtD = dist[cur] + wt;

                if (fl >= cap || nxtD >= dist[nxt]) continue;

                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};

                if (!in_q[nxt]) {
                    q.push(nxt);
                    in_q[nxt] = 1;
                }
            }
        }
        return dist[t] < INF;
    }

    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;

        while (find_path(s, t)) {
            for (int i = 0; i < n; i++) {
                pi[i] = min(pi[i] + dist[i], INF);
            }

            ll f = INF;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                f = min(f, edges[i].cap - edges[i].flow);
            }

            flow += f;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
            }
        }

        for (size_t i = 0; i < edges.size() / 2; i++) {
            cost += edges[i * 2].cost * edges[i * 2].flow;
        }

        return {flow, cost};
    }
};

vector<bool> find_articulation_points(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
    vector<bool> is_articulation_point(n, false);
    int timer = 0;
    function<void(int, int)> dfs = [&visited, &tin, &low, &is_articulation_point, &timer, &adj, &dfs](int v, int p) -> void {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    is_articulation_point[v] = true;
                ++children;
            }
        }
        if(p == -1 && children > 1)
            is_articulation_point[v] = true;
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i, -1);
    }
    return is_articulation_point;
}

class Block3Checkers {
public:
    int flowcnt = 0;
    int do_flow(vector<string>& a, pii l1, pii l2) {
        flowcnt ++;
        vvi in(n, vi(n)), out(n, vi(n));
        int idptr = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                in[i][j] = idptr ++;
                out[i][j] = idptr ++;
            }
        }
        int ssource = idptr ++, ssink = idptr ++;
        UCF_MCMF mcmf(idptr);
        mcmf.addEdge(ssource, out[l1.first][l1.second], 1e9, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(a[i][j] == 'N') continue;
                mcmf.addEdge(in[i][j], out[i][j], 1, 0);
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if(a[i][j] == 'N') continue;
                    mcmf.addEdge(out[i][j], in[nr][nc], 1e9, 0);
                }
            }
        }
        mcmf.addEdge(in[l2.first][l2.second], ssink, 1e9, 0);
        return mcmf.calc(ssource, ssink).first;
    }

    vi dr8 = {-1, -1, -1, 0, 1, 1, 1, 0};
    vi dc8 = {-1, 0, 1, 1, 1, 0, -1, -1};
    bool check_around(vector<string>& a, pii loc) {
        int cnt = 0;
        for(int i = 0; i < 8; i++){
            int nr = loc.first + dr8[i], nc = loc.second + dc8[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) {cnt ++; continue;}
            if(a[nr][nc] == 'N') cnt ++;
        }
        return cnt >= 1;
    }

    int isocnt = 0;
    bool is_iso(vector<string>& a, pii loc) {
        isocnt ++;
        vvb v(n, vb(n, false));
        queue<pii> q;
        v[loc.first][loc.second] = true;
        q.push(loc);
        while(q.size() != 0){
            int r = q.front().first, c = q.front().second;
            q.pop();
            if(a[r][c] == 'A' && (r != loc.first || c != loc.second)) return false;
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(a[nr][nc] == 'N') continue;
                if(v[nr][nc]) continue;
                v[nr][nc] = true;
                q.push({nr, nc});
            }
        }
        return true;
    }

    //finds an articulation point connected to the component loc is in
    pii find_arti(vector<string>& a, pii loc) {
        vvi c(n * n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(a[i][j] == 'N') continue;
                int ind = i * n + j;
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k], nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if(a[nr][nc] == 'N') continue;
                    int nid = nr * n + nc;
                    c[ind].push_back(nid);
                }
            }
        }
        vb arti = find_articulation_points(n * n, c);
        queue<pii> q;
        q.push(loc);
        vvb v(n, vb(n, false));
        v[loc.first][loc.second] = true;
        while(q.size() != 0){
            int r = q.front().first, c = q.front().second;
            q.pop();
            int id = r * n + c;
            if(arti[id] && (r != loc.first || c != loc.second)) return {r, c};
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i], nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(v[nr][nc]) continue;
                v[nr][nc] = true;
                q.push({nr, nc});
            }
        }
        return {-1, -1};
    }

    int solve(vector<string>& a, vector<pii> loc) {
        int ans = 1e9;
        //isolate loc[0], then check flow between loc[1], loc[2]
        if(is_iso(a, loc[0])) { //0 extra
            // cout << "ISO : " << loc[0].first << " " << loc[0].second << "\n";
            ans = min(ans, do_flow(a, loc[1], loc[2]));
            // cout << "FLOW : " << do_flow(a, loc[1], loc[2]) << "\n";
        }
        for(int i = 0; i < n * n; i++){
            int r1 = i / n, c1 = i % n;
            if(a[r1][c1] != '.') continue;
            if(!check_around(a, {r1, c1})) continue;
            a[r1][c1] = 'N';
            if(is_iso(a, loc[0])) {
                ans = min(ans, do_flow(a, loc[1], loc[2]) + 1);
                a[r1][c1] = '.';
                continue;
            }
            for(int j = 0; j < n * n; j++){
                int r2 = j / n, c2 = j % n;
                if(a[r2][c2] != '.') continue;
                if(!check_around(a, {r2, c2})) continue;
                a[r2][c2] = 'N';
                if(is_iso(a, loc[0])) {
                    ans = min(ans, do_flow(a, loc[1], loc[2]) + 2);
                    a[r2][c2] = '.';
                    continue;
                }
                //find where to put the third blocker
                pii arti = find_arti(a, loc[0]);
                int r3 = arti.first, c3 = arti.second;
                if(r3 != -1 && a[r3][c3] == '.' && ans > 5) {
                    a[r3][c3] = 'N';
                    if(check_around(a, {r3, c3}) && is_iso(a, loc[0])) {
                        ans = min(ans, do_flow(a, loc[1], loc[2]) + 3);
                    }
                    a[r3][c3] = '.';
                }
                a[r2][c2] = '.';
            }
            a[r1][c1] = '.';
        }
        //3 extra
        {
            vector<pii> ch;
            for(int i = 0; i < 4; i++){
                int nr = loc[0].first + dr[i], nc = loc[0].second + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(a[nr][nc] == 'N') continue;
                ch.push_back({nr, nc});
                a[nr][nc] = 'N';
            }
            ans = min(ans, do_flow(a, loc[1], loc[2]) + (int) ch.size());
            for(pii x : ch) a[x.first][x.second] = '.';
        }
        return ans;
    }

    int blockThem(vector<string> board) {
        n = board.size();
        //check if answer == 100
        vector<pii> loc;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] != 'A') continue;
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if(board[nr][nc] == 'A') return 100;
                }
                loc.push_back({i, j});
            }
        }
        //otherwise, answer <= 6
        int ans = 6;
        ans = min(ans, solve(board, {loc[0], loc[1], loc[2]}));
        ans = min(ans, solve(board, {loc[1], loc[0], loc[2]}));
        ans = min(ans, solve(board, {loc[2], loc[1], loc[0]}));
        // cout << "ISOCNT : " << isocnt << "\n";
        // cout << "FLOWCNT : " << flowcnt << "\n";
        return ans;
    }
};

int main() {
    int n0; cin >> n0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> arg0(n0);
    for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
    auto c = Block3Checkers();
    int ret = c.blockThem(arg0);
    cout << ret;
}