#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1948C

//we can just do BFS over the grid to figure out where we can go. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<char>> g(2, vector<char>(n));
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < n; j++){
                cin >> g[i][j];
            }
        }
        queue<pair<int, int>> q;
        vector<vector<bool>> v(2, vector<bool>(n, false));
        q.push({0, 0});
        v[0][0] = true;
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        while(q.size() != 0){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= 2 || nc >= n){
                    continue;
                }
                if(g[nr][nc] == '<') {
                    nc --;
                }
                else {
                    nc ++;
                }
                if(!v[nr][nc]) {
                    v[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        cout << (v[1][n - 1]? "YES" : "NO") << "\n";
    }
    
    return 0;
}
