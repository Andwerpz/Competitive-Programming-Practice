#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, n;
    cin >> r >> n;
    if(r == n){
        cout << "too late\n";
        return 0;
    }
    set<int> s;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        s.insert(x);
    }
    for(int i = 1; i <= r; i++){
        if(s.find(i) == s.end()) {
            cout << i << "\n";
            break;
        }
    }
    
    return 0;
}
