#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

//SWERC 2020 - M

//each picture will be composed purely of a bunch of alternating concentric black and 
//white components. Let's call such a picture a 'bullseye'

//first, if the two pictures have a different amount of rings, or the outer ring in the
//two pictures are different, then it's impossible to transform, as the constraints on
//morphing forbid us to decrease the amount of components.

//otherwise, it's always possible.
//the idea is that we can always transform an arbitrary bullseye into a canonical 
//form C by making the rings as large as possible, and since the operations are reversible,
//we can just reverse the sequence of moves required to go from G2 -> C to get C -> G2,
//and therefore get G1 -> C -> G2

//some notes on generating G -> C:
// - make sure that every morph preserves the lack of 'diagonal' 2x2 in the grid.
// - make sure that every morph doesn't disconnect a component. 

//since the bounds are quite small, you can be rather inefficient.
//i think this solution runs in O(W^2 * H^2)

vi dr = {-1, 1, 0, 0};
vi dc = {0, 0, -1, 1};

vector<vector<int>> gen_d(vector<string>& g) {
    int n = g.size(), m = g[0].size();
    vector<vector<int>> d(n, vector<int>(m, 1e9));
    d[0][0] = 0;
    priority_queue<pair<int, pii>> q;
    q.push({0, {0, 0}});
    while(q.size() != 0) {
        int r = q.top().second.first;
        int c = q.top().second.second;
        int cdist = -q.top().first;
        q.pop();
        if(cdist != d[r][c]) continue;
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            int ndist = cdist + (g[r][c] != g[nr][nc]);
            if(ndist < d[nr][nc]) {
                d[nr][nc] = ndist;
                q.push({-ndist, {nr, nc}});
            }
        }
    }
    return d;
}

int mxd(vector<string>& g) {
    vector<vi> d = gen_d(g);
    int n = g.size(), m = g[0].size();
    int ret = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        ret = max(ret, d[i][j]);
    }
    return ret;
}

vector<pair<int, int>> gen_seq(vector<string> g) {
    // cout << "GEN SEQ" << endl;
    vector<vi> d = gen_d(g);
    vector<pii> ans;
    int dlim = mxd(g);
    int n = g.size(), m = g[0].size();
    for(int dptr = 1; dptr <= dlim; dptr++) {
        vector<vector<bool>> v(n, vector<bool>(m, false));
        queue<pii> q;
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            if(d[i][j] != dptr - 1) continue;
            bool valid = false;
            for(int k = 0; k < 4; k++) {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(d[nr][nc] == dptr) valid = true;
            }
            if(valid) {
                q.push({i, j});
                v[i][j] = true;
            }
        }
        while(q.size() != 0) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            assert(d[r][c] == dptr - 1);
            assert(v[r][c]);
            if(r < dptr || c < dptr || n - r - 1 < dptr || m - c - 1 < dptr) continue;
            //check diag rule
            if(r != 0 && c != 0 && d[r - 1][c - 1] == dptr && d[r - 1][c] == dptr - 1 && d[r][c - 1] == dptr - 1) {
                q.push({r, c});
                continue;
            }
            if(r != 0 && c != m - 1 && d[r - 1][c + 1] == dptr && d[r - 1][c] == dptr - 1 && d[r][c + 1] == dptr - 1) {
                q.push({r, c});
                continue;
            }
            if(r != n - 1 && c != 0 && d[r + 1][c - 1] == dptr && d[r + 1][c] == dptr - 1 && d[r][c - 1] == dptr - 1) {
                q.push({r, c});
                continue;
            }
            if(r != n - 1 && c != m - 1 && d[r + 1][c + 1] == dptr && d[r + 1][c] == dptr - 1 && d[r][c + 1] == dptr - 1) {
                q.push({r, c});
                continue;
            }
            //check if we're disconnecting a component
            if(r != 0 && c != 0 && r != n - 1 && c != m - 1) {
                if(d[r - 1][c] == dptr && d[r + 1][c] == dptr && d[r][c - 1] == dptr - 1 && d[r][c + 1] == dptr - 1) {
                    q.push({r, c});
                    continue;
                }
                if(d[r - 1][c] == dptr - 1 && d[r + 1][c] == dptr - 1 && d[r][c - 1] == dptr && d[r][c + 1] == dptr) {
                    q.push({r, c});
                    continue;
                }
            }
            //flip here
            ans.push_back({r, c});
            d[r][c] = dptr;
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(d[nr][nc] != dptr - 1) continue;
                if(v[nr][nc]) continue;
                v[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return ans;
}

void sim(vector<string> g, vector<pair<int, int>> ans) {
    for(pii x : ans) {
        int r = x.first;
        int c = x.second;
        g[r][c] = (g[r][c] == '.')? '#' : '.';

        for(int i = 0; i < g.size(); i++) cout << g[i] << "\n";
        cout << "\n";
    }   
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m; 
    cin >> m >> n;
    vector<string> g1(n), g2(n);
    for(int i = 0; i < n; i++) cin >> g1[i];
    for(int i = 0; i < n; i++) cin >> g2[i];
    //check impossible
    if(mxd(g1) != mxd(g2) || g1[0][0] != g2[0][0]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    //gen ans
    vector<pair<int, int>> s1 = gen_seq(g1);
    vector<pair<int, int>> s2 = gen_seq(g2);
    reverse(s2.begin(), s2.end());
    vector<pair<int, int>> ans;
    for(int i = 0; i < s1.size(); i++) {
        ans.push_back(s1[i]);
    }
    for(int i = 0; i < s2.size(); i++) {
        ans.push_back(s2[i]);
    }

    assert(ans.size() <= 250000);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i].second << " " << ans[i].first << "\n";
    }
    // sim(g1, ans);

    return 0;
}
