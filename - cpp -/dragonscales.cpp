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

//UTPC Contest 1-29-25 Div.1 - G

//just use prefix sums to do the derivative, then take the prefix sums of the derivative
//to get the actual answer

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> m >> n;
    vvi d(m, vi(3));
    for(int i = 0; i < m; i++){
        cin >> d[i][0] >> d[i][1] >> d[i][2];
        d[i][0] --;
    }
    vl pfx(n + 1, 0);
    for(int i = 0; i < m; i++){
        ll l = d[i][0], r = d[i][1], p = d[i][2];
        pfx[l] += p, pfx[r] -= p;
    }
    for(int i = 1; i <= n; i++) pfx[i] += pfx[i - 1];
    for(int i = 0; i < m; i++){
        ll l = d[i][0], r = d[i][1], p = d[i][2];
        pfx[r] -= p * (r - l);
    }
    for(int i = 1; i <= n; i++) pfx[i] += pfx[i - 1];
    for(int i = 0; i < n; i++) cout << pfx[i] << " ";
    cout << "\n";

    return 0;
}