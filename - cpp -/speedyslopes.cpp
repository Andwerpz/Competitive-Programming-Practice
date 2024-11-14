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

//Alberta Collegiate Programming Contest 2024 - J

//dijkstra with pruning. 

//naively, we can think of a dijkstra solution where each node would be described by which cell we're in, and our current
//speed. However, that would be O(nm * 2000), which is around 2*10^7, and dijkstra would definitely TLE. 

//However, while doing dijkstra, we can prune out some nodes depending on what nodes we've visited before. Specifically,
//if we've visited some cell (r, c), speed v, at time t, then it's strictly worse to visit (r, c) with lower
//speed and higher time. 

//As dijkstra's guarantees that we visit nodes in increasing time, all we have to do is check if the max speed
//at our current cell (r, c) is \geq our current speed, and if so, we can prune out the current search. This pruning
//is enough to get AC, however idk what the time complexity is. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi h(n, vi(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> h[i][j];
        }
    }
    int b;
    cin >> b;
    set<pair<pii, pii>> bs;
    for(int i = 0; i < b; i++){
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        bs.insert({{r1, c1}, {r2, c2}});
    }
    vi dr = {-1, -1, -1, 0, 0, 1, 1, 1};
    vi dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    priority_queue<pair<ld, pair<pii, int>>> q;
    q.push({0, {{0, 0}, 0}});
    vvi maxs(n, vi(m, -1));
    vector<vvd> d(n, vvd(m, vd(2000 + 1, 1e18)));
    d[0][0][0] = 0;
    ld ans = 1e18;
    while(q.size() != 0){
        int r = q.top().second.first.first;
        int c = q.top().second.first.second;
        int vel = q.top().second.second;
        ld t = -q.top().first;
        q.pop();
        //check if we should stop
        if(maxs[r][c] >= vel) {
            continue;
        }
        maxs[r][c] = vel;
        if(r == n - 1 && c == m - 1){
            ans = t;
            break;
        }
        for(int i = 0; i < 8; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            int nvel = vel + h[r][c] - h[nr][nc];
            if(bs.count({{r, c}, {nr, nc}})) {
                nvel *= 2;
            }
            nvel = min(nvel, 2000);
            if(nvel <= 0 || maxs[nr][nc] >= nvel){
                continue;
            }
            ld nt = t;
            if(abs(dr[i]) + abs(dc[i]) == 2){
                nt += 150.0 / nvel;
            }
            else {
                nt += 100.0 / nvel;
            }
            if(d[nr][nc][nvel] <= nt) {
                continue;
            }
            d[nr][nc][nvel] = nt;
            q.push({-nt, {{nr, nc}, nvel}});
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}