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

//Codeforces - 2B

//observe that the number of trailing 0s is equal to the number of powers of 10, and 10 = 2 * 5

//consider powers of 2 and 5 separately. Actually, you can just take the minimum one, and that will restrict
//the number of 10s. 

//you have to be careful if there exists a '0' in the grid, as if you take it, the amount of trailing 0s
//is fixed to 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi g(n, vi(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> g[i][j];
    vvi a(n, vi(n)), b(n, vi(n));
    bool zex = false;
    int zr, zc;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        int tmp = g[i][j];
        if(tmp == 0) {
            zex = true;
            zr = i, zc = j;
            a[i][j] = 1e9;
            b[i][j] = 1e9;
            continue;
        }
        while(tmp % 2 == 0) {
            tmp /= 2;
            a[i][j] ++;
        }
        while(tmp % 5 == 0) {
            tmp /= 5;
            b[i][j] ++;
        }
    }
    vvl dpa(n, vl(n, 1e9)), dpb(n, vl(n, 1e9));
    dpa[0][0] = 0, dpb[0][0] = 0;
    vvl pva(n, vl(n, -1)), pvb(n, vl(n, -1));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        //down
        if(i != n - 1 && dpa[i][j] + a[i][j] < dpa[i + 1][j]) {
            pva[i + 1][j] = 0;
            dpa[i + 1][j] = dpa[i][j] + a[i][j];
        }
        if(i != n - 1 && dpb[i][j] + b[i][j] < dpb[i + 1][j]) {
            pvb[i + 1][j] = 0;
            dpb[i + 1][j] = dpb[i][j] + b[i][j];
        }
        //right
        if(j != n - 1 && dpa[i][j] + a[i][j] < dpa[i][j + 1]) {
            pva[i][j + 1] = 1;
            dpa[i][j + 1] = dpa[i][j] + a[i][j];
        }
        if(j != n - 1 && dpb[i][j] + b[i][j] < dpb[i][j + 1]) {
            pvb[i][j + 1] = 1;
            dpb[i][j + 1] = dpb[i][j] + b[i][j];
        }
    }
    ll ansc;
    string ans = "";
    if(dpa[n - 1][n - 1] + a[n - 1][n - 1] < dpb[n - 1][n - 1] + b[n - 1][n - 1]) {
        ansc = dpa[n - 1][n - 1] + a[n - 1][n - 1];
        int r = n - 1, c = n - 1;
        while(r != 0 || c != 0) {
            if(pva[r][c] == 0) {
                ans.push_back('D');
                r --;
            }
            else {
                ans.push_back('R');
                c --;
            }
        }
    }
    else {
        ansc = dpb[n - 1][n - 1] + b[n - 1][n - 1];
        int r = n - 1, c = n - 1;
        while(r != 0 || c != 0) {
            if(pvb[r][c] == 0) {
                ans.push_back('D');
                r --;
            }
            else {
                ans.push_back('R');
                c --;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    if(ansc > 1 && zex) {
        ans = "";
        for(int i = 0; i < zr; i++) ans.push_back('D');
        for(int i = 0; i < n - 1; i++) ans.push_back('R');
        for(int i = 0; i < (n - 1) - zr; i++) ans.push_back('D');
        ansc = 1;
    }
    cout << ansc << "\n";
    cout << ans << "\n";
    
    return 0;
}