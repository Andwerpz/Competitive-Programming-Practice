#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC131A

//if we have an unlimited amount of digits, we can 'seperate' where we put a and b into the number so that when
//doubling it, they don't interfere with each other. 

//luckily, since a and b are less than 10^8, this is possible with 18 digits. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b;
    cin >> a >> b;
    ll ans = a + (b * (ll) 1e10) / 2;
    cout << ans << "\n";
    
    return 0;
}
