#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1934C

//testing distance from a corner gives us one diagonal where a mine has to be. 
//if we test distance from two corners on the same side, then the intersection between the two diagonals is
//the location where the mine likely is, but since there are two mines, we don't know for sure. 

//the solution is to test distances at 3 corners, and take note of the two intersection points; there must exist
//a mine at one of the intersection points. 

//using our fourth and last query, we can simply test one of them to see if there is a mine there. 

//below is the derivation for the intersection points given distances from two corners. 

//(x - 1) + (y - 1) = d0
//(n - x) + (y - 1) = t_int
//x = d0 - y + 2
//n - (d0 - y + 2) + y - 1 = t_int
//2y - d0 - 3 + n = t_int
//2y = t_int + d0 + 3 - n
//y = (t_int + d0 + 3 - n) / 2

//(n - x) + (m - y) = d1
//(n - x) + (y - 1) = t_int
//x + y - n - m = -d1
//x = n + m - d1 - y
//n - (n + m - d1 - y) + y - 1 = t_int
//2y + d1 - m - 1 = t_int
//2y = t_int - d1 + m + 1
//y = (t_int - d1 + m + 1) / 2

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int m0x, m0y, m1x, m1y;
        int d0, d1, t_int;
        cout << "? " << 1 << " " << 1 << endl;
        cin >> d0;
        cout << "? " << n << " " << m << endl;
        cin >> d1;
        cout << "? " << n << " " << 1 << endl;
        cin >> t_int;
        m0y = (t_int + d0 + 3 - n) / 2;
        m0x = d0 - m0y + 2;
        m1y = (t_int - d1 + m + 1) / 2;
        m1x = - d1 + n + m - m1y;
        if(m0y <= 0 || m0x <= 0){
            swap(m0x, m1x);
            swap(m0y, m1y);
        }
        cout << "? " << m0x << " " << m0y << endl;
        int test;
        cin >> test;
        if(test == 0){
            cout << "! " << m0x << " " << m0y << endl;
        }
        else {
            cout << "! " << m1x << " " << m1y << endl;
        }
    }
    
    return 0;
}
