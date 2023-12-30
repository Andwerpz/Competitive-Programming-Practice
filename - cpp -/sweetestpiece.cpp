#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 E

//since the grid size is so small, we can just simulate all the pours using BFS

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> h(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> h[i][j];
        }
    }
    vector<vector<int>> nr(n, vector<int>(m, 0));
    vector<vector<int>> v(n, vector<int>(m, -1));
    vector<int> dr = {-1, -1, 1, 1};
    vector<int> dc = {-1, 0, 1, 0};
    for(int i = 0; i < q; i++){
        int r, c;
        cin >> r >> c;
        r --;
        c --;
        queue<pair<int, int>> q;
        v[r][c] = i;
        q.push({r, c});
        while(q.size() != 0){
            int cur_r = q.front().first;
            int cur_c = q.front().second;
            int cur_h = h[cur_r][cur_c];
            q.pop();
            nr[cur_r][cur_c] ++;
            for(int j = 0; j < 4; j++){
                int nr = cur_r + dr[j];
                int nc = cur_c + dc[j];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) {
                    continue;
                }
                if(h[nr][nc] > cur_h){
                    continue;
                }
                if(v[nr][nc] == i){
                    continue;
                }
                v[nr][nc] = i;
                q.push({nr, nc});
            }
        }
    }
    int max_nr = -1;
    int ans_r = -1;
    int ans_c = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(nr[i][j] > max_nr) {
                max_nr = nr[i][j];
                ans_r = i;
                ans_c = j;
            }
        }
    }
    ans_r ++;
    ans_c ++;
    cout << ans_r << " " << ans_c << " " << max_nr << "\n";
    
    return 0;
}
