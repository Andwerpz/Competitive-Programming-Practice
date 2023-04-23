#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest D

//the situation is identical to starting at 0, and trying to find the minimum moves to get to -d. 

//the minimum moves to get from 0 to 0 is lcm(wrap, d) / d, where wrap is the distance to wrap around
//to get the actual answer, just subtract 1. 

ll solve(ll start, ll wrap, ll step) {
    //cout << "SOLVE : " << start << " " << wrap << " " << step << "\n";
    ll cnt = (wrap - start) / step;
    ll ptr = start + cnt * step;
    ll ans = cnt;
    if(ptr == wrap){
        return ans;
    }
    ptr = (ptr + step) - wrap;
    //go forwards
    ll fstep = ptr;
    ll bstep = step - ptr;
    ans = min(solve(0, step, fstep) * (cnt + 1), solve(0, step, bstep) * cnt + 1);
    return ans;
}

ll gcd(ll a, ll b) {
    return b == 0? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll wrap = 1;
    for(int i = 0; i < 32; i++){
        wrap *= (ll) 2;
    }
    ll d;
    cin >> d;
    //cout << wrap << "\n";
    while(d % 2 == 0){
        d /= 2;
        wrap /= 2;
    }
    ll lcm = (wrap * d) / gcd(wrap, d);
    cout << (lcm / d) - 1 << "\n";
    //cout << solve(0, wrap, d) - 1 << "\n";
    
    return 0;
}
