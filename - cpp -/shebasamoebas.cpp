#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 03 E

//basic grid floodfill. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> dr = {1, -1, 0, 0, 1, 1, -1, -1};
    vector<int> dc = {0, 0, 1, -1, 1, -1, 1, -1};
    vector<string> a(n);
    vector<vector<bool>> v(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(v[i][j] || a[i][j] == '.') {
                continue;
            }
            ans ++;
            stack<pair<int, int>> s;
            s.push({i, j});
            v[i][j] = true;
            while(s.size() != 0) {
                int r = s.top().first;
                int c = s.top().second;
                s.pop();
                for(int k = 0; k < 8; k++){
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m) {
                        continue;
                    }
                    if(!v[nr][nc] && a[nr][nc] == '#') {
                        s.push({nr, nc});
                        v[nr][nc] = true;
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
