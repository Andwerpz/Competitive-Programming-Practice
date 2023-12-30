#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC129A

//use divide and conquer to solve. 

//if x shares the most significant bit with n, then x ^ n < n holds. 
//otherwise, it never holds. 

ll solve(ll l, ll r, ll n, ll bit) {
    //cout << "SOLVING : "<< l << " " << r << " " << bit << endl;
    if(r <= l) {
        return 0;
    }
    if(bit == -1){
        return 0;
    }
    bool has = (n >> bit) & 1;
    ll ans = 0;
    if(has) {
        //cout << "HAS" << "\n";
        //any number with the bit will work
        if(r >= ((ll) 1 << bit)) {
            if(l >= ((ll) 1 << bit)) {
                return r - l;
            }
            return solve(l, ((ll) 1 << bit), n, bit - 1) + (r - ((ll) 1 << bit));
        }
        else {
            return solve(l, r, n, bit - 1);
        }
    }
    else {
        //cout << "NOT HAS" << "\n";
        //any number with the bit cannot work
        if(l >= ((ll) 1 << bit)) {
            return 0;
        }
        return solve(l, min(r, ((ll) 1 << bit)), n, bit - 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, l, r;
    cin >> n >> l >> r;
    r ++;
    cout << solve(l, r, n, 60) << "\n";
    
    return 0;
}
