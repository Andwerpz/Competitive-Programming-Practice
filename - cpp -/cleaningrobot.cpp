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

//ICPC NAC 2021 - C

//problem description is very vague about what it means for a robot to be able to clean everything. 
//Here are my assumptions:
// - for a robot of size x to clean everything, there must be some x by x square of unobstructed space to initially
//   place the robot
// - any unobstructed cell must be a part of a x by x unobstructed square, so the robot can potentially reach it
// - all x by x squares must be reachable from every other x by x square, that is the graph must be connected. 

//we can do binary search on x, and check each x in O(nm) time using 2D prefix sums. 

vvi pfx;
int query(int l1, int r1, int l2, int r2) {
    if(l1 > l2) swap(l1, l2);
    if(r1 > r2) swap(r1, r2);
    return pfx[l2][r2] - pfx[l1][r2] - pfx[l2][r1] + pfx[l1][r1];
}

/*
1 0 0 0 0 0 -1 0
0 1 1 1 1 1 1 0
0 1 1 1 1 1 1 0
0 1 1 1 1 1 1 0
0 1 1 1 1 1 1 0 
-1 1 1 1 1 1 (1) 0
0 0 0 0 0 0 0 0
*/

vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
bool is_valid(int n, int m, vvi& g, int sz) {
    // cout << "CHECK VALID : " << sz << endl;
    //check if robot can fit everywhere
    vvi a(n + 1, vi(m + 1, 0));
    vvb val(n - sz + 1, vb(m - sz + 1, false));
    for(int i = 0; i + sz <= n; i++){
        for(int j = 0; j + sz <= m; j++){
            if(query(i, j, i + sz, j + sz) == 0) {
                a[i][j] ++;
                a[i + sz][j] --;
                a[i][j + sz] --;
                a[i + sz][j + sz] ++;
                val[i][j] = true;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i != 0) a[i][j] += a[i - 1][j];
            if(j != 0) a[i][j] += a[i][j - 1];
            if(i != 0 && j != 0) a[i][j] -= a[i - 1][j - 1];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 0 && a[i][j] == 0) {
                return false;
            }
        }
    }
    //check for connectivity
    vvb v(n - sz + 1, vb(m - sz + 1, false));
    queue<pii> q;
    for(int i = 0; i + sz <= n; i++){
        for(int j = 0; j + sz <= m; j++){
            if(val[i][j]) {
                q.push({i, j});
                v[i][j] = true;
                goto found_first;
            }
        }
    }
    found_first: {}
    while(q.size() != 0){
        int r = q.front().first, c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int nr = r + dr[i], nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n - sz + 1 || nc >= m - sz + 1) continue;
            if(!val[nr][nc]) continue;
            if(v[nr][nc]) continue;
            v[nr][nc] = true;
            q.push({nr, nc});
        }
    }
    for(int i = 0; i + sz <= n; i++){
        for(int j = 0; j + sz <= m; j++){
            if(val[i][j] && !v[i][j]) return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vvi g(n, vi(m, 0));
    for(int i = 0; i < k; i++){
        int r, c;
        cin >> r >> c;
        r --, c --;
        g[r][c] = 1;
    }
    pfx = vvi(n + 1, vi(m + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++){
            pfx[i][j] = pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1] + g[i - 1][j - 1];
        }
    }
    if(!is_valid(n, m, g, 1)) {
        cout << "-1\n";
        return 0;
    }
    int low = 1, high = min(n, m);
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(n, m, g, mid)) ans = mid, low = mid + 1;
        else high = mid - 1;
    }
    cout << ans << "\n";
    
    return 0;
}