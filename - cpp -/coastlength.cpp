#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 08 A

//for each tile of sea, check for adjacent land tiles. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 2, vector<int>(m + 2, 0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            a[i + 1][j + 1] = s[j] == '0'? 0 : 1;
        }
    }
    vector<vector<bool>> v(n + 2, vector<bool>(m + 2, false));
    v[0][0] = true;
    stack<pair<int, int>> s;
    s.push({0, 0});
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int ans = 0;
    while(s.size() != 0){
        int r = s.top().first;
        int c = s.top().second;
        s.pop();
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= a.size() || nc >= a[0].size()) {
                continue;
            }
            if(a[nr][nc] == 1){
                ans ++;
                continue;
            }
            if(v[nr][nc]) {
                continue;
            }
            v[nr][nc] = true;
            s.push({nr, nc});
        }
    }
    cout << ans << "\n";
    
    return 0;
}
