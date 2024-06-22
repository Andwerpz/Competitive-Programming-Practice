#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1520G

//to handle the portals, we can use an auxillary node. Every portal will connect to a 'portal node' with the respective
//cost for that portal. 
//initially, it seems like running dijkstra's on this graph will solve the problem, but it turns out they tuned
//the time limit and constraints such that this solution doesn't work. We need a linear time solution. 

//The observation that makes it possible is that we only should use the portal exactly once. If we want to go from
//portal A to B, then C to D, we might as well just go directly from A to D, saving us the cost from portals
//B and C. 

//So, it is simply sufficient to BFS from the start and end cells, and then test the portals in the regions we can visit
//from the start and end cells. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m, w;
    cin >> n >> m >> w;
    vector<vector<ll>> a(n, vector<ll>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    //do grid search from beginning
    vector<vector<ll>> ds(n, vector<ll>(m, 1e18));
    ds[0][0] = 0;
    {
        queue<pair<int, int>> q;
        q.push({0, 0});
        while(q.size() != 0){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(a[nr][nc] == -1){
                    continue;
                }
                if(ds[r][c] + w >= ds[nr][nc]) {
                    continue;
                }
                ds[nr][nc] = ds[r][c] + w;
                q.push({nr, nc});
            }
        }
    }
    //do grid search from end
    vector<vector<ll>> de(n, vector<ll>(m, 1e18));
    de[n - 1][m - 1] = 0;
    {
        queue<pair<int, int>> q;
        q.push({n - 1, m - 1});
        while(q.size() != 0){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(a[nr][nc] == -1){
                    continue;
                }
                if(de[r][c] + w >= de[nr][nc]) {
                    continue;
                }
                de[nr][nc] = de[r][c] + w;
                q.push({nr, nc});
            }
        }
    }
    //portals?
    ll ans = ds[n - 1][m - 1];
    ll ps = 1e18;
    ll pe = 1e18;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            if(a[i][j] <= 0){
                continue;
            }
            ps = min(ps, ds[i][j] + a[i][j]);
            pe = min(pe, de[i][j] + a[i][j]);
        }
    }
    ans = min(ans, ps + pe);
    cout << (ans == 1e18? -1 : ans) << "\n";
    
    return 0;
}