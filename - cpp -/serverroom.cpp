#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int P = 998244353;

// ICPC PACNW 2025 - J

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    auto tp = [](vector<vector<int>> a) -> vector<vector<int>> {
        vector<vector<int>> res(a[0].size(), vector<int>(a.size()));
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < a[i].size(); j++) {
                res[j][i] = a[i][j];
            }
        }
        return res;
    };

    auto upd = [&](array<int,2> &cur, array<int,2> add) -> void {
        if(add[0] > cur[0]) {
            cur = add;
        } else if(add[0] == cur[0]) {
            cur[1] += add[1];
            if(cur[1] >= P) cur[1] -= P;
        }
    };

    //returns {max color, # ways}
    auto get_ways = [&](vector<vector<int>> grid) -> array<int,2> {

        // cout << "grid\n";
        // for(int i = 0; i < grid.size(); i++) {
        //     for(int x : grid[i]) cout << x;
        //     cout << '\n';
        // }

        //make second dimension smaller
        if(grid.size() < grid[0].size()) grid = tp(grid);

        int n = grid.size(), m = grid[0].size();

        //{cnt on, # ways}
        vector<array<int,2>> dp(1 << m, {-1,0});
        vector<array<int,2>> ndp(1 << m, {-1, 0});

        dp[0] = {0, 1};

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ndp.assign(1 << m, {-1, 0});

                for(int bm = 0; bm < 1 << m; bm++) {

                    if(dp[bm][0] != -1) {
                        //transition this light off to next
                        {
                            int nbm = bm & (~(1 << j));
                            upd(ndp[nbm], dp[bm]);
                        }
                        //transition this light on to next
                        {
                            int ok = grid[i][j];
                            if((bm >> j) & 1) ok = 0;
                            if(j && ((bm >> (j - 1)) & 1)) ok = 0;
                            if(ok) {
                                int nbm = bm | (1 << j);
                                upd(ndp[nbm], {dp[bm][0] + 1, dp[bm][1]});
                            }
                        }
                    }

                }
                dp = ndp;
            }
        }

        array<int,2> res = {-1,0};
        for(int bm = 0; bm < 1 << m; bm++) upd(res, dp[bm]);
        // cout << "cnt : " << res[0] << " ways : " << res[1] << '\n';
        return res;
    };

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '2') {
                // cnt++;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m) a[ni][nj] = '0';
                }
            }
        }
    }

    int res = 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '1') {
                vector<array<int,2>> vis;
                queue<array<int,2>> q;
                q.push({i, j});
                int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
                while(q.size()) {
                    auto [x, y] = q.front();
                    q.pop();
                    if(a[x][y] != '1') continue;
                    a[x][y] = '0';
                    vis.push_back({x, y});
                    minx = min(minx, x);
                    miny = min(miny, y);
                    maxx = max(maxx, x);
                    maxy = max(maxy, y);
                    for(int k = 0; k < 4; k++) {
                        int nx = x + dx[k], ny = y + dy[k];
                        if(nx >= 0 && nx < n && ny >= 0 && ny < m) q.push({nx, ny});
                    }
                }

                vector<vector<int>> grid(maxx - minx + 1, vector<int>(maxy - miny + 1));
                for(auto [x, y] : vis) {
                    grid[x - minx][y - miny] = 1;
                }

                auto [add_cnt, ways] = get_ways(grid);
                cnt += add_cnt;

                res = 1LL * res * ways % P; 

            }
        }
    }

    cout << cnt << " " << res << '\n';

    return 0;
}