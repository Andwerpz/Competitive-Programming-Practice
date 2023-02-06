#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using pi = pair<int, int>;
bool visited[105][105];
vector<string> g;
int n, m;

//ICPC North America Qualifier 2022 E

// return whether we ate a dot
bool dfs(pi coords, bool first) {
    int i = coords.first, j = coords.second;
    if (i >= n) return false;
    if (j >= m) return false;
    if (i < 0) return false;
    if (j < 0) return false;
    // if (g[i][j] != '.' && g[i][j] != ' ' && )
    if (g[i][j] == 'X') return false;
    if (!first) {
        if (g[i][j] != '.' && g[i][j] != ' ') return false;
    }
    if (visited[i][j]) return false;
    visited[i][j] = true;
    bool new_dot = g[i][j] == '.';
    new_dot |= dfs({i+1, j}, false);
    new_dot |= dfs({i-1, j}, false);
    new_dot |= dfs({i, j+1}, false);
    new_dot |= dfs({i, j-1}, false);
    return new_dot;
}



int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    
    // ifstream cin ("test.in");
    
    cin >> n >> m;

    string s;
    while (getline(cin, s)) {
        if (!s.size()) continue;
        // cerr << "s : " << s << endl;
        g.push_back(s);
    }
    // cerr << "after : " << s << endl;
    memset(visited, 0, sizeof(visited));

    vector<pi> entrances;
    // cerr << "READIN\n";
    // for (auto s : g) cerr << s << endl;
    // for (int i = 0; i < n; ++i) cerr << g[i] << endl;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            assert(i < g.size());
            assert(j < g[i].size());
            if (g[i][j] == 'X') continue;
            if (g[i][j] == '.') continue;
            if (g[i][j] == ' ') continue;

            entrances.push_back({i,j});
        }
    }

    int players_needed = 0, dots_left = 0;
    for (auto p : entrances) {
        // cerr << "i : " << p.first << " j : " << p.second << " g[i][j] : " << g[p.first][p.second] << endl;
        if (dfs(p, true)) players_needed++;
    }
            // cerr << "hey\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j]) continue;
            if (g[i][j] == '.') dots_left++;
        }
    }
    cout << players_needed << " " << dots_left << endl;
    return 0;
}