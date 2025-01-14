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

//Codeforces - 1611G

//we can greedily assign paths to fulfill one diagonal at a time. 
//define a diagonal to be all cells (r, c) that satisfy r + c = D, for some arbitrary D. We'll iterate 
//D from 0 to n + m - 2, and satisfy them one at a time. 

//for each diagonal, we'll iterate in ascending r. for each cell on the diagonal, (r, c), we'll maintain
//how many paths are currently going through that cell. If a[r][c] == 0, then there's no need for a path
//to be going through, but if a[r][c] == 1, then we have to have at least 1 path.

//where do we get this path? First, we can see if cell (r - 1, c - 1) has any paths that we can take. Since
//we've already satisfied any candies on that diagonal, we can freely take paths from that cell. 
//Second, we can see if there are any paths behind us on the same diagonal. We can use a stack to keep
//track of these. 

//otherwise, we need to add a new path here. We don't care about where it comes from, just that it
//eventually goes through the current cell. 

//note that we shouldn't 'leave paths behind', always make sure to bring paths from previous diagonals along
//as they might be useful in the future. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi a(n, vi(m));
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = 0; j < m; j++){
                a[i][j] = s[j] - '0';
            }
        }
        vvi p(n, vi(m, 0));
        for(int _ = 0; _ <= n + m - 2; _++){
            int r = 0, c = _;
            if(c >= m) r = c - (m - 1), c = m - 1;
            stack<pii> s;
            while(r < n && c >= 0){
                if(r - 1 >= 0 && c - 1 >= 0) {
                    p[r][c] += p[r - 1][c - 1];
                    p[r - 1][c - 1] = 0;
                }
                if(a[r][c] && p[r][c] == 0) {
                    if(s.size() != 0){
                        int nr = s.top().first, nc = s.top().second;
                        p[r][c] ++;
                        p[nr][nc] --;
                        if(p[nr][nc] == 0) s.pop();
                    }
                    else p[r][c] ++;
                }
                if(c + 1 == m && r + 1 < n && c - 1 >= 0) p[r + 1][c - 1] += p[r][c], p[r][c] = 0;
                if(p[r][c] != 0) s.push({r, c});
                r ++, c --;
            }
        }
        int ans = 0;
        for(int i = 0; i < m; i++){
            ans += p[n - 1][i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}