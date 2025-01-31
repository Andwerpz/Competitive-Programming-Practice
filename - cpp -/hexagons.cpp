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

//Codeforces - 1421D

//first, we can replace any move with two adjacent moves, so for example C_2 = C_1 + C_3. We can then minimize the cost 
//for any move by doing a bunch of substitutions. 

//after minimizing the cost for each move, we can just take the most direct path to each target hexagon. 
//At this point, we have to do some casework, but it's not too bad. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll x, y;
        cin >> x >> y;
        vl c(6);
        for(ll& _ : c) cin >> _;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 6; j++) c[j] = min(c[j], c[(j - 1 + 6) % 6] + c[(j + 1) % 6]);
        }
        ll ans = 1e18;
        vector<pll> dir = {{1, 1}, {0, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, 0}};
        if(x < 0 && y < 0){
            if(x < y) {
                ans = (y - x) * c[2] + abs(y) * c[3];
            }
            else { //x >= y
                ans = (x - y) * c[4] + abs(x) * c[3];
            }
        }
        else if(x >= 0 && y >= 0){
            if(x < y) {
                ans = (y - x) * c[1] + x * c[0];
            }
            else { //x >= y
                ans = (x - y) * c[5] + y * c[0];
            }
        }
        else if(x < 0 && y >= 0){
            ans = abs(x) * c[2] + y * c[1];
        }
        else {  //x >= 0 && y < 0
            ans = x * c[5] + abs(y) * c[4];
        }
        cout << ans << "\n";
    }
    
    return 0;
}