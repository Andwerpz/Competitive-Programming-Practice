#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1909D

//always try to simplify the problem before solving - tourist i think.

//first, identify the situations where it is impossible: 
//note that if we apply operations to an element x, and x > k, then at least one of the 'children' of x must
//remain above k. Same goes for if x < k. If x == k, then in order to make all the 'children' equal, they must 
//all equal k. So it must be the case that all elements are either above, below, or equal to k. 

//next, we simplify the operation. For now, let's assume that a[i] > k. 
//note that when all the elements are equal, all of the elements are still going to be > k; each element starts out
//greater than k, and when we add a new element, we always add an extra k of value to the new element. 
//then, we can notice that if we presubtract all elements with k; a[i] := a[i] - k, and we set k := 0, 
//then this problem is identical. 

//if k == 0, then we're pretty much trying to find a divisor d such that it divides all a[i], and d is maximized. 
//we can do this just by finding the gcd of all the elements, and that is the optimal divisor. 

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int nr_below = 0;
        int nr_above = 0;
        int nr_equal = 0;
        for(int i = 0; i < n; i++){
            if(a[i] < k){
                nr_below ++;
            }
            else if(a[i] > k) {
                nr_above ++;
            }
            else {
                nr_equal ++;
            }
        }
        if((nr_below == 0) + (nr_above == 0) + (nr_equal == 0) != 2) {
            cout << "-1\n";
            continue;
        }
        if(nr_equal == n) {
            cout << "0\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            a[i] = abs(a[i] - k);
        }
        ll g = a[0];
        for(int i = 1; i < n; i++){
            g = gcd(g, a[i]);
        }
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans += (a[i] / g) - 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
