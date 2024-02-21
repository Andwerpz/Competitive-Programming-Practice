#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - A

//first, find the big tromino that the point is in, then figure out which of the 4 sub trominos inside the big
//one contains it. We can just keep doing this until we hit the base tromino that the point is in. 

bool is_inside(ll x, ll y, ll sq_len) {
    return (x < sq_len && y < 2 * sq_len) || (x < 2 * sq_len && y < sq_len);
}

ll get_sq_len(ll x, ll y){
    ll sq_len = 1;
    while(!is_inside(x, y, sq_len)) {
        sq_len *= 2;
    }   
    return sq_len;
}

int convert_to_rel(ll& x, ll& y, ll sq_len) {
    ll sm_sq = sq_len / 2;
    if(x >= sm_sq && x < 3 * sm_sq && y >= sm_sq && y < 3 * sm_sq) {
        x -= sq_len / 2;
        y -= sq_len / 2;
        return 0;
    }
    else if(y >= sq_len) {
        y = 2 * sq_len - y - 1;
        swap(x, y);
        return 1;
    }
    else if(x >= sq_len) {
        x = 2 * sq_len - x - 1;
        swap(x, y);
        return 3;
    }
    else {
        return 0;
    }
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll x, y;
        cin >> x >> y;
        int ans = 0;
        while(true) {
            ll sq_len = get_sq_len(x, y);
            if(sq_len == 1){
                break;
            }
            ans = (ans + convert_to_rel(x, y, sq_len)) % 4;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
