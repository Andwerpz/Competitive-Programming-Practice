#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986A

//you can just pick one of the points. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b, c;
        cin >> a >> b >> c;
        cout << min({abs(a - b) + abs(a - c), abs(b - a) + abs(b - c), abs(c - a) + abs(c - b)}) << "\n";
    }
    
    return 0;
}