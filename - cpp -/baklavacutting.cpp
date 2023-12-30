#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 A

//note that the cut out portion will always just be half of the original, so we just divide the total area by 2 
//k times to get the final area. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld l;
    int k;
    cin >> l >> k;
    ld area = l * l;
    for(int i = 0; i < k; i++){
        area /= 2.0;
    }
    cout << fixed << setprecision(10) << area << "\n";
    
    return 0;
}
