#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - D

//just try a random square, and get the distance, d. 
//then, try all squares that are exactly distance d away. Hopefully there aren't too many of them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cnt; cin >> cnt;
    // int trycnt = 0;
    while(cnt) {

        cout << "0 0" << endl;
        // trycnt++;
        // assert(trycnt < 1000);
        ll dist; cin >> dist;
        if(dist == 0) {
            cnt--;
            continue;
        }
        for(ll x = 0; x <= 1000000; x++) {
            ll left = dist - x * x;
            ll y = (ll) sqrt(left + 0.000001);
            if(y * y == left && y >= 0 & y <= 1000000) {
                if(cnt) {
                    cout << x << " " << y << endl;
                    // trycnt++;
                    // assert(trycnt < 1000);
                    ll val; cin >> val;
                    if(val == 0) {
                        cnt--;
                    }
                }
            }
        }

    }
    
    return 0;
}
