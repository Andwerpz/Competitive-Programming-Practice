#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 N

//i have no idea how this solution works

//greedily fill shopping bags. 

//first, put as much as you can of the larger item into the bag, then fill the rest of the space with 
//as much of the smaller item.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll t, n1, n2, s1, s2;
    cin >> t >> n1 >> n2 >> s1 >> s2;
    ll ans = 0;
    if(s1 < s2) {
        ll tmp = s1;
        s1 = s2;
        s2 = tmp;
        tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    while(n1 + n2 != 0){
        ans ++;
        ll ptr = t;
        ll diff = min(n1, ptr / s1);
        n1 -= diff;
        ptr -= diff * s1;
        diff = min(n2, ptr / s2);
        n2 -= diff;
    }
    cout << ans << "\n";
    
    return 0;
}
