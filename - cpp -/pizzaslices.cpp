#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - B

//the amount of slices needs to be enough to feed everyone, and evenly divisible by the number of people. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k;
    cin >> n >> m >> k;
    n *= 8;
    cout << (((n >= m * k) && ((n % m) == 0))? "TRUE" : "FALSE") << "\n";
    
    return 0;
}
