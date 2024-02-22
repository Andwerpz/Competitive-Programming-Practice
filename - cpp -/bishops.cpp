#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(!cin.eof()) {
        if(n == 1){
            cout << 1 << "\n";
        }
        else {
            cout << n * 2 - 2 << "\n";
        }
        cin >> n;
    }   
    
    return 0;
}
