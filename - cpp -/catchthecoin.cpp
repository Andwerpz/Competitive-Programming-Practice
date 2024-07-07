#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1989A

//I claim that you can catch any coin with y >= -1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    while(n--){
        int x, y;
        cin >> x >> y;
        y ++;
        cout << (y < 0? "NO\n" : "YES\n");
    }
    
    return 0;
}