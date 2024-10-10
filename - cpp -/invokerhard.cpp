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

//Calgary 2022 - I

//just compute the quaternion inverse of b.

vd quat_mult(vd a, vd b) {
    vd res = vd(4, 0);
    res[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    res[1] = a[1] * b[0] + a[0] * b[1] - a[3] * b[2] + a[2] * b[3];
    res[2] = a[2] * b[0] + a[3] * b[1] + a[0] * b[2] - a[1] * b[3];
    res[3] = a[3] * b[0] - a[2] * b[1] + a[1] * b[2] + a[0] * b[3];
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vd a(4), b(4);
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    cin >> b[0] >> b[1] >> b[2] >> b[3];
    vd c(4);
    c[0] = b[0];
    c[1] = -b[1];
    c[2] = -b[2];
    c[3] = -b[3];
    ld len = b[0] * b[0] + b[1] * b[1] + b[2] * b[2] + b[3] * b[3];
    c[0] /= len;
    c[1] /= len;
    c[2] /= len;
    c[3] /= len;
    a = quat_mult(a, c);
    cout << fixed << setprecision(10) << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << "\n";
    
    return 0;
}