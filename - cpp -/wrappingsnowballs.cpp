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

//Alberta Collegiate Programming Contest 2024, Open Division - D

//surface area covered is exactly equal to the surface area of the solid angle distance R_ball
//with angular radius R_i / R_ball radians. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld pi = acos(-1);
    ld r;
    int n;
    cin >> r >> n;
    for(int i = 0; i < n; i++){
        ld ri;
        cin >> ri;
        ld angr = ri / r;
        angr = min(angr, pi);
        ld sang = 2.0 * pi * (1.0 - cos(angr));
        ld area = sang * r * r;
        area = min(area, 4.0 * pi * r * r);
        // cout << "SANG : " << sang << "\n";
        // cout << "ANGR : " << angr << "\n";
        cout << fixed << setprecision(10) << area << "\n";
    }
    
    return 0;
}