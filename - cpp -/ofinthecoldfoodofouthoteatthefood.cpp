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

//University of Alberta Programming Contest 2025 Open - E

//we can fix the desired temperature = 1. Then, the rate at which the food heats up with respect to time
//is 1 / T, if the oven is at the desired temperature. 

//However, we need to account for the time before the oven reaches the desired temperature. If t < H, then the 
//instantaneous rate at which it's heating up is (t / H) / T, or t / HT. Integrating, we get t^2 / 2HT. 

//we can either solve for when the definite integral = 1, or just do binary search.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld t, h;
    cin >> t >> h;
    ld epsilon = 1e-9;
    ld low = 0, high = 1e15;
    while(high - low > epsilon){
        ld mid = low + (high - low) / 2;
        ld ctemp = 0;
        if(mid < h){
            ctemp += mid * mid / (2.0 * h * t);
        }
        else {
            ctemp += h * h / (2.0 * h * t);
            ctemp += (mid - h) / t;
        }
        if(ctemp < 1.0) low = mid;
        else high = mid;
    }
    cout << fixed << setprecision(10) << low << "\n";
    
    return 0;
}