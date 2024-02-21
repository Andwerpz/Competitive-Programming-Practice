#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - C

//worst case is either everyone takes pizza, or everyone takes tacos. We can simulate both cases. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int x, y, z;
    cin >> x >> y >> z;
    z = min(z / 2, n);
    if(x - n * 2 - z < 0 || y - n * 2 - z < 0){
        cout << "yes\n";
    }
    else {
        cout << "no\n";
    }
    
    return 0;
}
