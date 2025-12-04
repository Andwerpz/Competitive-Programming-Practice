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

//Mines HSPC 2025 Open Division - H

//avoid floating point errors by adding epsilon. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld x, y, z;
    cin >> x >> y >> z;
    ld avg = x * 0.25 + y * 0.25 + z * 0.5;
    avg += 1e-9;
    if(avg >= 90) {
        cout << "A\n";
    }
    else if(avg >= 80) {
        cout << "B\n";
    }
    else if(avg >= 70) {
        cout << "C\n";
    }
    else if(avg >= 60) {
        cout << "D\n";
    }
    else {
        cout << "F\n";
    }
    
    return 0;
}