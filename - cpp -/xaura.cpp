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

//Codeforces - 2045G

//nice problem that makes use of knowledge on potential fields and curl

//notice that if there exists a negative loop, then all the paths are invalid, as you can just go to the loop, go around it 
//a bunch of times, and go to your destination
//so, in what grids are there no negative loops? If between two cells there are two paths with differing costs to get between 
//them, then there exists a negative loop. This is because travelling on a path backwards negates the cost.
//Recall from calc 3 that there is a name for such a structure where the cost between any two points is fixed regardless of 
//path taken: we are looking for a potential grid. Also remember from calc 3 that a field is a potential field iff it's curl free.

//once we've determined that some grid is a potential grid, then we can just do a single source BFS, and take the difference in
//potential for any two cells to get their cost. 

ll powll(ll a, ll b) {
    ll res = 1;
    for(int i = 0; i < b; i++) res *= a;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, x;
    cin >> n >> m >> x;
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            g[i][j] = s[j] - '0';
        }
    }
    //determine whether this graph is a potential graph
    bool ispot = true;
    if(x != 1) {
        for(int i = 0; i < n - 1; i++){
            for(int j = 0; j < m - 1; j++){
                ll sum = 0;
                sum += powll(g[i][j] - g[i + 1][j], x);
                sum += powll(g[i + 1][j] - g[i + 1][j + 1], x);
                sum += powll(g[i + 1][j + 1] - g[i][j + 1], x);
                sum += powll(g[i][j + 1] - g[i][j], x);
                if(sum != 0) ispot = false;
            }
        }
    }
    vvl p(n, vl(m));
    if(ispot){
        p[0][0] = 0;
        vvb v(n, vb(m, false));
        v[0][0] = true;
        queue<pii> q;
        q.push({0, 0});
        vi dr = {-1, 1, 0, 0};
        vi dc = {0, 0, -1, 1};
        while(q.size() != 0){
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(v[nr][nc]) continue;
                v[nr][nc] = true;
                ll cost = powll(g[r][c] - g[nr][nc], x);
                p[nr][nc] = p[r][c] + cost;
                q.push({nr, nc});
            }
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int rs, cs, rf, cf;
        cin >> rs >> cs >> rf >> cf;
        rs --, cs --, rf --, cf --;
        if(!ispot) cout << "INVALID\n";
        else cout << p[rf][cf] - p[rs][cs] << "\n";
    }
    
    return 0;
}