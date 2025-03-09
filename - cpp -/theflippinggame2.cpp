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

//Topcoder - 14844

//just flip one tile over and over again. Can just try everything. 

int solve(int n, int m, vector<string> a, char ecol) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) if(a[i][j] == 'e') a[i][j] = ecol;
    }
    vi dr = {-1, 1, 0, 0};
    vi dc = {0, 0, -1, 1};
    int ans = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            vvi d(n, vi(m, 1e9));
            d[i][j] = 0;
            priority_queue<pair<int, pii>> q;
            q.push({0, {i, j}});
            while(q.size() != 0){
                int r = q.top().second.first;
                int c = q.top().second.second;
                int cdist = -q.top().first;
                q.pop();
                if(d[r][c] != cdist) continue;
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                    int ndist = cdist + (a[r][c] != a[nr][nc]);
                    if(ndist < d[nr][nc]) {
                        d[nr][nc] = ndist;
                        q.push({-ndist, {nr, nc}});
                    }
                }
            }
            int cans = 0;
            for(int ii = 0; ii < n; ii++){
                for(int jj = 0; jj < m; jj++){
                    cans = max(cans, d[ii][jj]);
                }
            }
            cans ++;
            ans = min(ans, cans);
        }
    }
    return ans;
}

class TheFlippingGame2 {
public:
    int MinimumMoves(int n, int m, vector<string> x) {
        return min(solve(n, m, x, 'b'), solve(n, m, x, 'w'));
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int n2; cin >> n2;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> arg2(n2);
    for (int i=0;i<n2;++i) { getline(cin, arg2[i]); }
    auto c = TheFlippingGame2();
    int ret = c.MinimumMoves(arg0, arg1, arg2);
    cout << ret;
}