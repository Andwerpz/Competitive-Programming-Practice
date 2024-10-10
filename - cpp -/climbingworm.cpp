#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - climbingworm

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, h;
    int cur = 0;
    cin >> a >> b >> h;
    int ans = 0;
    while(cur < h) {
        ans ++;
        cur += a;
        if(cur >= h){
            break;
        }
        cur -= b;
    }
    cout << ans << "\n";
    
    return 0;
}
