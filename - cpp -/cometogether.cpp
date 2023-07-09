#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1845B

//we just need to check if bob and carol move together in the x direction and y direction, and how much

//note that on the grid, if you need to move i units in the x direction, and j units in the y direction, you can
//do the moves in any order. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int ax, ay, bx, by, cx, cy;
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        int bdx = bx - ax;
        int bdy = by - ay;
        int cdx = cx - ax;
        int cdy = cy - ay;
        int ans = 0;
        if((bdx < 0) == (cdx < 0)) {
            ans += min(abs(bdx), abs(cdx));
        }
        if((bdy < 0) == (cdy < 0)){
            ans += min(abs(bdy), abs(cdy));
        }
        ans ++;
        cout << ans << "\n";
    }
    
    return 0;
}
