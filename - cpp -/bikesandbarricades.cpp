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

//2024 ICPC NAQ - B

//implementation. 

ld lerp(ld x0, ld t0, ld x1, ld t1, ld t) {
    return x0 + (x1 - x0) * ((t - t0) / (t1 - t0));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    bool hit = false;
    ld ans = 1e18;
    for(int i = 0; i < n; i++){
        ld x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        if((x1 < 0 && x2 < 0) || (x1 > 0 && x2 > 0)){
            continue;
        }
        ld hitpos = lerp(y1, x1, y2, x2, 0);
        if(hitpos < 0){
            continue;
        }
        hit = true;
        ans = min(ans, hitpos);
    }
    cout << fixed << setprecision(10) << (hit? ans : -1) << "\n";
    
    return 0;
}