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

//AtCoder - ABC366D

//direct application of 3D prefix sum

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, q;
    cin >> n;
    vector<vvl> a(n + 1, vvl(n + 1, vl(n + 1, 0)));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++){
                cin >> a[i][j][k];
                a[i][j][k] += a[i - 1][j][k] + a[i][j - 1][k] + a[i][j][k - 1];
                a[i][j][k] -= a[i - 1][j - 1][k] + a[i][j - 1][k - 1] + a[i - 1][j][k - 1];
                a[i][j][k] += a[i - 1][j - 1][k - 1];
            }
        }
    }
    cin >> q;
    for(int i = 0; i < q; i++){
        int x1, x2, y1, y2, z1, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        x1 --;
        y1 --;
        z1 --;
        ll ans = a[x2][y2][z2];
        ans -= a[x1][y2][z2] + a[x2][y1][z2] + a[x2][y2][z1];
        ans += a[x1][y1][z2] + a[x2][y1][z1] + a[x1][y2][z1];
        ans -= a[x1][y1][z1];
        cout << ans << "\n";
    }
    
    return 0;
}