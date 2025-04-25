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

//Spring 2025 Columbia University Local Contest - E

//consider x and y seperately. 

//observe that the expected x value is simply px * n - qx * n, similar story for y. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ld px, qx, py, qy;
        cin >> px >> qx >> py >> qy;
        ld ansx = px * n - qx * n, ansy = py * n - qy * n;
        cout << fixed << setprecision(10) << ansx << " " << ansy << "\n";
    }
    
    return 0;
}