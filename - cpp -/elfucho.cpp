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

//Codeforces - 2155A

//make sure not to misread, they're asking for the number of *games* played, not rounds. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int a = n, b = 0;
        int ans = 0;
        while(!(a == 1 && b == 1)) {
            ans += a / 2 + b / 2;
            int na = (a + 1) / 2;
            int nb = (b + 1) / 2 + (a - na);
            a = na, b = nb;
            // cout << "A B : " << a << " " << b << "\n";
        }
        ans ++;
        cout << ans << "\n";
    }
    
    return 0;
}