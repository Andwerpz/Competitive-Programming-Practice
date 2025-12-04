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

//Mines HSPC 2025 Open Division - N

//binary search across v. 

bool is_valid(vd& d, vd& w, ld l, ld v) {
    ld pt = 0, pp = 0;
    for(int i = 0; i < d.size(); i++){
        ld nt = pt + (d[i] - pp) / v;
        nt = max(nt, d[i]);
        nt += w[i];
        pt = nt, pp = d[i];
    }
    ld ft = pt + (l - pp) / v;
    return ft <= l;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    ld l;
    cin >> n >> l;
    vd d(n), w(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    for(int i = 0; i < n; i++) cin >> w[i];
    ld low = 1, high = 1e9;
    ld ans = high;
    ld epsilon = 1e-9;
    while(high - low > epsilon) {
        ld mid = low + (high - low) / 2;
        if(is_valid(d, w, l, mid)) ans = mid, high = mid;
        else low = mid;
    }
    if(ans > 3 * 1e8) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}