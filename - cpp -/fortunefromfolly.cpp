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

//Kattis - fortunefromfolly

//we only care about the results from the last N case openings, so we can say that our state is a length-N bitstring 
//a terminal state is one where the popcount is >= K. Let's compute the expected number of moves to get from some bitstring
//S to a terminal state. 

//for |S| < k
//e[S] = p * e[(S << 1) ^ 1] + (1 - p) e[(S << 1) ^ 0] + 1
//e[S] - p * e[(S << 1) ^ 1] - (1 - p) e[(S << 1) ^ 0] = 1
//for |S| >= k
//e[S] = 0

//so this is just a system of 2^N linear equations, since N = 6, we can solve using gaussian elimination. 

void solve(int n, vvd& mat, vd& vec, vd& ans) {
    if(n == 0) return;
    assert(mat[n - 1][n - 1] != 0.0);
    for(int i = 0; i < n - 1; i++) mat[n - 1][i] /= mat[n - 1][n - 1];
    vec[n - 1] /= mat[n - 1][n - 1];
    mat[n - 1][n - 1] = 1.0;
    for(int i = 0; i < n - 1; i++) {
        ld mult = mat[i][n - 1] / mat[n - 1][n - 1];
        for(int j = 0; j < n - 1; j++) {
            mat[i][j] -= mat[n - 1][j] * mult;
        }
        vec[i] -= vec[n - 1] * mult;
        mat[i][n - 1] = 0;
    }
    solve(n - 1, mat, vec, ans);
    ans[n - 1] = vec[n - 1];
    for(int i = 0; i < n - 1; i++) {
        ans[n - 1] -= ans[i] * mat[n - 1][i];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    ld p;
    cin >> p;
    vvd mat((1 << n), vd((1 << n), 0));
    vd vec((1 << n), 0.0);
    for(int i = 0; i < (1 << n); i++) {
        if(__builtin_popcount(i) >= k) {
            vec[i] = 0.0;
            mat[i][i] = 1.0;
        }
        else {
            vec[i] = 1.0;
            mat[i][i] = 1.0;
            mat[i][(((1 << n) - 1) & (i << 1)) ^ 1] += -p;
            mat[i][(((1 << n) - 1) & (i << 1)) ^ 0] += -(1 - p);
        }
    }
    vd ans((1 << n), 0.0);
    solve((1 << n), mat, vec, ans);
    cout << fixed << setprecision(10) << ans[0] << "\n";
    
    return 0;
}