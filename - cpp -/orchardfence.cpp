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

ld calc(int ind, vector<pll>& a, int n) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k, d;
    cin >> n >> k >> d;
    vector<pll> a(n);
    for(int i = 0; i < n; i++) {
        ld x, y;
        cin >> x >> y;
        x *= 100;
        y *= 100;
        a[i] = {round(x), round(y)};
    }
    ld ans = 0;
    for(int i = 0; i < n; i++) {
        ans += calc(i, a, n);
    }
    ans /= 100;
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}