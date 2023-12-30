#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC 2023–2024 NERC D

//if at some point, b^k % n === 0, then we can use kind 1. 
//if at some point, b^k % n === 1, then we can use kind 2.
//if at some point, b^k % n === -1, then we can use kind 3.

//the justification for kind 1 is pretty obvious. 
//for kind 2, we notice that b^k * b^k or b^(2k) % n === 1 as well, same goes for any multiple of k. 
//for kind 3, whether or not it's positive or negative depends on the parity of k, thus it alternates. 

//we just find the earliest k at which any kind is satisfied. Note that we only have to iterate k at most
//n times, before the value of b^k % n becomes cyclic. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        set<int> v;
        ll b, n;
        cin >> b >> n;
        ll ptr = 1;
        ll k = 0;
        ll a = -1;
        bool found = false;
        while(true) {
            ptr = (ptr * b) % n;
            k ++;
            if(v.find(ptr) != v.end()) {
                break;
            }   
            v.insert(ptr);
            if(ptr == 0 || ptr == 1 || ptr == n - 1){
                found = true;
                a = ptr == 0? 1 : (ptr == 1? 2 : 3);
                break;
            }
        }
        if(found) {
            cout << a << " " << k << "\n";
        }
        else {
            cout << "0\n";
        }
    }
    
    return 0;
}
