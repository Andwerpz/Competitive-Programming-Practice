#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC137A

//just brute force D:

ll gcd(ll a, ll b){
    if(a == 0){
        return b;
    }
    return gcd(b % a, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll l, r;
    cin >> l >> r;
    ll diff = r - l;
    while(true) {
        ll y = r;
        ll x = y - diff;
        while(x >= l) {
            if(gcd(x, y) == 1){
                cout << diff << "\n";
                return 0;
            }
            x --;
            y --;
        }
        diff --;
    }
    
    return 0;
}
