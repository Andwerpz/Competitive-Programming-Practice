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

//2025 NAQ - B

//to get the closest tower, we can do a BFS starting from each tower. 
//to get the second closest tower, we can extend the BFS starting from each tower. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    queue<array<int, 3>> q; //{tower, r, c};
    vvi v1(n, vi(m, -1)), v2(n, vi(m, -1));
    for(int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        r --;
        c --;
        v1[r][c] = i + 1;
        q.push({i + 1, r, c});
    }
    vi dr = {-1, 1, 0, 0};
    vi dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int t = q.front()[0];
        int r = q.front()[1];
        int c = q.front()[2];
        q.pop();
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(v1[nr][nc] == t) continue;
            if(v1[nr][nc] != -1 && v2[nr][nc] != -1) continue;
            if(v1[nr][nc] == -1) {
                v1[nr][nc] = t;
                q.push({t, nr, nc});
            }
            else if(v2[nr][nc] == -1) {
                v2[nr][nc] = t;
                q.push({t, nr, nc});
            }
            else assert(false);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << v1[i][j] << " ";
        }
        cout << "\n";
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << v2[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}