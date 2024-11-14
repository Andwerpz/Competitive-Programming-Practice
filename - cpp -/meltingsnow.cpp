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

//Alberta Collegiate Programming Contest 2024, Open Division - L

//the snow will stabilize when the amount of snow melting equals the amount of snow falling, or when
//T * P = S, where T is the total amount of snow. So T = S / P. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld s, p;
    cin >> s >> p;
    p /= 100.0;
    ld ans = s * (1.0 / p);
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}