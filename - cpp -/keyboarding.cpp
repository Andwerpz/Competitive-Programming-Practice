#include <bits/stdc++.h>
using namespace std;
// using int = long long;
using pi = pair<int, int>;

//ICPC World Finals 2015 F

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    // ifstream cin ("test.in");
    
    int n, m; cin >> n >> m;
    vector<string> g(n);

    cin.ignore();

    for (auto& s : g) getline(cin, s);

    string s; cin >> s;

    // cerr << "s : " << s << endl;

    map<char, vector<pi>> c2ps;


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            c2ps[g[i][j]].push_back({i, j});
        }
    }


    vector<vector<vector<pi>>> adj(n, vector<vector<pi>>(m));

    // left
    for (int i = 0; i < n; ++i) {
        int last = -1;
        for (int j = 1; j < m; ++j) {
            if (g[i][j] != g[i][j-1]) {
                last = j-1;
            }
            if (last != -1) {
                adj[i][j].push_back({i, last});
            }
        }
    }


    // right
    for (int i = 0; i < n; ++i) {
        int last = -1;
        for (int j = m-2; j > -1; --j) {
            if (g[i][j] != g[i][j+1]) {
                last = j+1;
            }
            if (last != -1) {
                adj[i][j].push_back({i, last});
            }
        }
    }

    // up
    for (int j = 0; j < m; ++j) {
        int last = -1;
        for (int i = 1; i < n; ++i) {
            if (g[i][j] != g[i-1][j]) {
                last = i-1;
            }
            if (last != -1) {
                adj[i][j].push_back({last, j});
            }
        }
    }

    // down
    for (int j = 0; j < m; ++j) {
        int last = -1;
        for (int i = n-2; i > -1; --i) {
            if (g[i][j] != g[i+1][j]) {
                last = i+1;
            }
            if (last != -1) {
                adj[i][j].push_back({last, j});
            }
        }
    }
    // for (auto p : adj[0][0]) {
    //     cerr << p.first << " " << p.second << endl;
    // }

    int ssi = s.size();

    // vector<vector<vector<int>>> dp(ssi + 2, vector<vector<int>> (n, vector<int>(m, 112345678)));
    vector<vector<int>> last(n, vector<int>(m, 112345678)), dp(n, vector<int>(m, 112345678));

    // dp[0][0][0] = 0;
    // last[0][0] = 0;

    for (int i = 1; i <= ssi + 1; ++i) {
        char curr = s[i-1];

        dp.assign(n, vector<int>(m, 112345678));

        // vector<vector<bool>> seen(n, vector<bool>(m));

        // priority_queue<pair<int, pi>> pq;
        queue<pair<int, pi>> q;

        // push all lasts
        if (i == 1) {
            // pq.push({0, {0, 0}});
            q.push({0, {0, 0}});
        } else {
            char lastc = s[i-2];
            // cerr << "i : " << i << " last : " << last << endl;
            vector<pair<int, pi>> to_push;
            for (auto p : c2ps[lastc]) {
                // pq.push({-last[p.first][p.second], {p.first, p.second}});
                // q.push({-last[p.first][p.second], {p.first, p.second}});
                to_push.push_back({-last[p.first][p.second], {p.first, p.second}});
            }
            while (to_push.size()) {
                auto p = to_push.back();
                q.push({p.first, {p.second.first, p.second.second}});
                to_push.pop_back();
            }
        }

        while (q.size()) {
            auto p = q.front();
            q.pop();
            int dist = -p.first;
            int row = p.second.first, col = p.second.second;
            // if (row < 0 || col < 0) continue;
            // if (row < 0) row = n-1;
            // if (row == n) row = 0;
            if (row < 0 || row >= n) continue;   

            // if (col < 0) col = m-1;
            // if (col == m) col = 0;
            if (col < 0 || col >= m) continue;
            // if (row >= n || col >= m) continue;
            if (dp[row][col] <= dist) continue;
            dp[row][col] = dist;
            // cerr << "dist : " << dist << " row : " << row << " col : " << col << endl;

            for (auto p : adj[row][col]) {
                // pq.push({-(dist+1), {p.first, p.second}});
                q.push({-(dist+1), {p.first, p.second}});
            }            
            // pq.push({-(dist+1), {row+1, col}});
            // pq.push({-(dist+1), {row, col+1}});
            // pq.push({-(dist+1), {row, col-1}});
            // pq.push({-(dist+1), {row-1, col}});
        }


        last = dp;

    }


    // for (auto v : dp[1]) {
    //     for (auto vy : v) {
    //         cerr << vy << " ";
    //     }
    //     cerr << endl;
    // }


    int ans = INT_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '*') ans = min(ans, dp[i][j]);
        }
    }


    cout << ans + ssi + 1 << endl;

    
    return 0;
}