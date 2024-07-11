#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1982B

//notice that after a bunch of moves, x will eventually be stuck into a cycle going from 1 -> y
//we can simply simulate the process until x gets to 1, and then simulation is unnecessary since it's in a cycle.

//to quickly simulate, we can just compute the number of moves required until x is divisible by y. 
//Since we just divide by y every time, the simulation will get to 1 in around log_y(x) timesteps. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x, y, k;
        cin >> x >> y >> k;
        while(x != 1) {
            int dist = y - (x % y);
            if(dist > k) {
                x += k;
                k = 0;
                break;
            }
            x += dist;
            while(x % y == 0){
                x /= y;
            }
            k -= dist;
        }
        k %= (y - 1);
        x += k;
        cout << x << "\n";
    }
    
    return 0;
}