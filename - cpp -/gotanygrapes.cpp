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

//Codeforces - 1114A

//just simulate problem statement. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int x, y, z, a, b, c;
    cin >> x >> y >> z >> a >> b >> c;
    if(x > a) {
        cout << "NO\n";
        return 0;
    }
    a -= x;
    if(y > a + b) {
        cout << "NO\n";
        return 0;
    }
    int diff = min(y, a);
    a -= diff;
    y -= diff;
    b -= y;
    if(z > a + b + c) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    
    return 0;
}