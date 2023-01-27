#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 E

//first, just do all the processes of length q, and then fit in the processes of length 1.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll q, m, s, l;
    cin >> q >> m >> s >> l;
    //do q
    ll ans = 0;
    ll qCycles = l / m;
    l -= (l / m) * m;
    ans += qCycles * q;
    ll rem = 0;
    if(l != 0){
        ans += q;
        rem = q * (m - l);
    }
    s -= rem;
    if(s > 0) {
        ans += s / m + (s % m == 0? 0 : 1);
    }
    cout << ans << "\n";
    
    return 0;
}
