#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1952I

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll a, b;
    char plus;
    cin >> a >> plus >> b;
    cout << a + b + a * a + b * b + a - b + abs(a) * 2 * b - (a * b + 2) << "\n";
    
    return 0;
}
