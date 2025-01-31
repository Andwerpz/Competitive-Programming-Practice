#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1644E

//If the moves entirely consist of 'R' or 'D', the answer is n. 
//otherwise, there must exist both 'R' and 'D' moves. 

//consider the tile that gets visited by the last move in the unmodified sequence. With modifications, we can make this
//tile visit any tile that is below and to the right of it. 

//Next, consider the second to last tile in the unmodified sequence. This tile can visit almost all the tiles that the last
//tile can visit, except for the ones blocked off due to the last tile not being able to travel outside of the grid boundaries.

//This pattern continues until we reach the tile that has min(x, y) = 0. This is because all the moves to get to this tile
//are just 'R' or 'D' so we can't move in the other dimension.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        string s;
        cin >> s;
        ll x = 0, y = 0;
        for(int i = 0; i < s.size(); i++){
            x += s[i] == 'R';
            y += s[i] == 'D';
        }
        if(min(x, y) == 0) {
            cout << n << "\n";
            continue;
        }
        ll dx = n - x, dy = n - y;
        ll ans = dx * dy;
        for(int i = s.size() - 1; i >= 0; i--){
            x -= s[i] == 'R';
            y -= s[i] == 'D';
            if(s[i] == 'R') ans += dy;
            if(s[i] == 'D') ans += dx;
            if(min(x, y) == 0) {ans += i; break;}
        }
        cout << ans << "\n";
    }
    
    return 0;
}