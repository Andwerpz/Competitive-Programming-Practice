#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//M(IT)^2 Winter 2025 Advanced Round 2 - P2

//we can check for 'bad' patterns in each query rectangle. If there are no bad patterns, then it's guaranteed
//that the entire rectangle consists of only snakes. 

//There are 3 bad patterns:
// - 3 horizontal elements of the same color
// - 3 vertical elements of the same color
// - 4 elements of the same color arranged in a 2x2 square

//we can use a 2D prefix sum to quickly query for the existence of bad elements in an arbitrary rectangle. 

int query(vvi& pfx, int r1, int c1, int r2, int c2) {
    if(r1 >= r2 || c1 >= c2) return 0;
    return pfx[r2][c2] - pfx[r1][c2] - pfx[r2][c1] + pfx[r1][c1];
}

void calc_pfx(vvi& a) {
    int n = a.size(), m = a[0].size();
    vvi pfx(n + 1, vi(m + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            pfx[i][j] = pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1] + a[i - 1][j - 1];
        }
    }
    a = pfx;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi a(n, vi(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cin >> a[i][j];
    }
    vvi bad_h(n, vi(m, 0)), bad_v(n, vi(m, 0)), bad_i(n, vi(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i >= 1 && i != n - 1 && a[i][j] == a[i + 1][j] && a[i][j] == a[i - 1][j]) bad_v[i][j] = 1;
            if(j >= 1 && j != m - 1 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j - 1]) bad_h[i][j] = 1;
            if(i != n - 1 && j != n - 1 && a[i][j] == a[i + 1][j] && a[i][j] == a[i][j + 1] && a[i][j] == a[i + 1][j + 1]) bad_i[i][j] = 1;
        }
    }
    calc_pfx(bad_h);
    calc_pfx(bad_v);
    calc_pfx(bad_i);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r2 ++, c2 ++;
        int bad = query(bad_v, r1 + 1, c1, r2 - 1, c2);
        bad += query(bad_h, r1, c1 + 1, r2, c2 - 1);
        bad += query(bad_i, r1, c1, r2 - 1, c2 - 1);
        cout << (bad? "NO" : "YES") << "\n";
    }
    
    return 0;
}