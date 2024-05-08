#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - skocimis

//pick the larger gap. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int a, b, c;
    cin >> a >> b >> c;
    cout << max(b - a, c - b) - 1 << "\n";
    
    return 0;
}
