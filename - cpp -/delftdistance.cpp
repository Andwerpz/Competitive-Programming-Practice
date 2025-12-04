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

//Kattis - delftdistance

//can just do dijkstra on graph. Have node for each corner and midpoint

const ld pi = acos(-1);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    //have distances for every corner and midpoint 
    //if there is a circle, then you can do some shortcutting
    int N = n * 2 + 1, M = m * 2 + 1;
    vvd d(N, vd(M, 1e18));
    vvb v(N, vb(M, false));
    d[0][0] = 0;
    priority_queue<pair<ld, pii>> q;
    q.push({0, {0, 0}});
    while(q.size() != 0){
        ld cdist = -q.top().first;
        int r = q.top().second.first, c = q.top().second.second;
        q.pop();
        // cout << "CDIST : " << cdist << " " << d[r][c] << "\n";
        if(d[r][c] != cdist) continue;
        if(v[r][c]) continue;
        v[r][c] = true;
        // cout << "RC : " << r << " " << c << "\n";
        if(r % 2 == 0 && c % 2 == 0) {
            //right
            if(c + 1 < M){
                int nr = r, nc = c + 1;
                ld ndist = cdist + 5.0;
                // cout << "NDIST : " << ndist << " " << d[nr][nc] << "\n";
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
            //down
            if(r + 1 < N){
                int nr = r + 1, nc = c;
                ld ndist = cdist + 5.0;
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
        }
        else if(r % 2 == 1) {
            //down
            if(r + 1 < N){
                int nr = r + 1, nc = c;
                ld ndist = cdist + 5.0;
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
            //down + right
            if(r + 1 < N && c + 1 < M && g[r / 2][c / 2] == 'O'){
                int nr = r + 1, nc = c + 1;
                ld ndist = cdist + (2.0 * pi * 5.0) / 4.0;
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
        }
        else if(c % 2 == 1){
            //right
            if(c + 1 < M){
                int nr = r, nc = c + 1;
                ld ndist = cdist + 5.0;
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
            //right + down
            if(r + 1 < N && c + 1 < M && g[r / 2][c / 2] == 'O'){
                int nr = r + 1, nc = c + 1;
                ld ndist = cdist + (2.0 * pi * 5.0) / 4.0;
                if(ndist < d[nr][nc]) {
                    d[nr][nc] = ndist;
                    q.push({-ndist, {nr, nc}});
                }
            }
        }
        else {
            //bruh
        }
    }
    cout << fixed << setprecision(10) << d[N - 1][M - 1] << "\n";
    
    return 0;
}