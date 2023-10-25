#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("test.in");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("test.out");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int caseno = 0;
    while(t--){
        caseno ++;
        cout << "Case #" << caseno << ": ";
        int n, m;
        cin >> n >> m;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        vector<vector<bool>> v(n, vector<bool>(m, false));
        vector<vector<int>> cap(n, vector<int>(m, 0));
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(g[i][j] != 'W') {
                    continue;
                }
                if(v[i][j]) {
                    continue;
                }
                v[i][j] = true;
                set<pair<int, int>> cap_loc;
                stack<pair<int, int>> s;
                int cnt = 0;
                s.push({i, j});
                while(s.size()) {
                    int r = s.top().first;
                    int c = s.top().second;
                    s.pop();
                    cnt ++;
                    for(int k = 0; k < 4; k++){
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= m) {
                            continue;
                        }
                        if(v[nr][nc]) {
                            continue;
                        }
                        if(g[nr][nc] == '.') {
                            cap_loc.insert({nr, nc});
                            continue;
                        }
                        if(g[nr][nc] != 'W') {
                            continue;
                        }
                        v[nr][nc] = true;
                        s.push({nr, nc});
                    }
                }
                if(cap_loc.size() == 1) {
                    cap[cap_loc.begin() -> first][cap_loc.begin() -> second] += cnt;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ans = max(ans, cap[i][j]);
            }
        }
        cout << (ans != 0? "YES" : "NO") << "\n";
        //cout << ans << "\n";
    }
    
    return 0;
}
