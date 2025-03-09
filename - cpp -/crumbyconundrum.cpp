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

//UTPC Contest 2-26-25 Div.1 - E

//can just compute the distance from each cell to the closest 'E'. Keep in mind some cells can't reach 
//an 'E' cell, but still can be spawnable. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    vvi d(n, vi(n, 1e9));
    queue<pii> qu;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(g[i][j] == 'E') {
                d[i][j] = 0;
                qu.push({i, j});
            }
        }
    }
    vi dr = {-1, 1, 0, 0};
    vi dc = {0, 0, -1, 1};
    while(qu.size() != 0){
        int r = qu.front().first;
        int c = qu.front().second;
        qu.pop();
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if(g[nr][nc] == '#') continue;
            int ndist = d[r][c] + 1;
            if(ndist < d[nr][nc]) {
                d[nr][nc] = ndist;
                qu.push({nr, nc});
            }
        }
    }
    int sum = 0;
    vi dcnt(n * n + 1, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            if(d[i][j] != 1e9 && d[i][j] != 0) {
                dcnt[d[i][j]] ++;
            }
            if(g[i][j] == '.') sum ++;
        }
    }
    // for(int i = 0; i < 5; i++){
    //     cout << dcnt[i] << " ";
    // }
    // cout << "\n";
    for(int i = 1; i < dcnt.size(); i++){
        dcnt[i] += dcnt[i - 1];
    }
    for(int i = 0; i < q; i++){
        int val;
        cin >> val;
        val --;
        cout << fixed << setprecision(10) << (ld) dcnt[val] / (ld) sum << "\n";
    }
    
    return 0;
}