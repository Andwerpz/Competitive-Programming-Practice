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

//Alberta Collegiate Programming Contest 2024, Open Division - A

//can just do bfs. Note that there are at most n * 4 + 1 valid positions, adjacent to any of the
//obstacles, and the starting position. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int w, h, sx, sy, n;
    cin >> w >> h >> sx >> sy >> n;
    map<int, set<int>> vmap, hmap;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        hmap[y].insert(x);
        vmap[x].insert(y);
    }
    if(sx == 0 || sy == 0 || sx == w - 1 || sy == h - 1){
        cout << "0\n";
        return 0;
    }
    map<pii, int> dist;
    queue<pii> q;
    q.push({sx, sy});
    dist[{sx, sy}] = 0;
    int ans = 1e9;
    while(q.size() != 0){
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        // cout << "DIST : " << cx << " " << cy << " " << dist[{cx, cy}] << "\n";
        auto hptr = hmap[cy].upper_bound(cx);
        if(hptr == hmap[cy].end()) {
            ans = min(ans, dist[{cx, cy}] + 1);
        }
        else {
            int nx = *hptr - 1;
            int ny = cy;
            if(!dist.count({nx, ny})) {
                q.push({nx, ny});
                dist[{nx, ny}] = dist[{cx, cy}] + 1;
            }
        }
        if(hptr != hmap[cy].begin()) {
            // cout << "CHECK BEFORE Y" << "\n";
            hptr --;
            if(hptr == hmap[cy].end()) {
                ans = min(ans, dist[{cx, cy}] + 1);
            }
            else {
                int nx = *hptr + 1;
                int ny = cy;
                if(!dist.count({nx, ny})) {
                    q.push({nx, ny});
                    dist[{nx, ny}] = dist[{cx, cy}] + 1;
                }
            }
        }
        auto vptr = vmap[cx].upper_bound(cy);
        if(vptr == vmap[cx].end()) {
            ans = min(ans, dist[{cx, cy}] + 1);
        }
        else {
            int nx = cx;
            int ny = *vptr - 1;
            if(!dist.count({nx, ny})) {
                q.push({nx, ny});
                dist[{nx, ny}] = dist[{cx, cy}] + 1;
            }
        }
        if(vptr != vmap[cx].begin()) {
            // cout << "CHECK BEFORE X" << "\n";
            vptr --;
            if(vptr == vmap[cx].end()) {
                ans = min(ans, dist[{cx, cy}] + 1);
            }
            else {
                int nx = cx;
                int ny = *vptr + 1;
                if(!dist.count({nx, ny})) {
                    q.push({nx, ny});
                    dist[{nx, ny}] = dist[{cx, cy}] + 1;
                }
            }
        }
    }
    if(ans == 1e9){
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}