#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1982A

//lets analyze the segments [x1, x2] and [y1, y2]. Notice that if one segment entirely
//contains another segment, then the scores must have been same at one point. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if((x1 <= y1 && x2 >= y2) || (y1 <= x1 && y2 >= x2)) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    
    return 0;
}