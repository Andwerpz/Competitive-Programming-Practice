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

//Mines HSPC 2025 Open Division - J

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, a;
    cin >> n >> a;
    n ++;
    bool is_valid = true;
    vi h(n);
    for(int i = 0; i < n; i++) cin >> h[i];
    for(int i = 1; i < n; i++) if(h[i] - h[i - 1] > a) is_valid = false;
    cout << (is_valid? "POSSIBLE" : "BUG REPORT") << "\n";
    
    return 0;
}