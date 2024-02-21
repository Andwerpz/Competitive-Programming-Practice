#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - L

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, lo, hi; cin >> n >> lo >> hi;
    int findlo = INT_MAX, findhi = INT_MIN;
    for(int i = 0; i < n - 1; i++) {
        int num; cin >> num;
        findlo = min(findlo, num);
        findhi = max(findhi, num);
    }
    // cout << "findlo : " << findlo << " findhi : " << findhi << '\n';
    if(findlo != lo && findhi != hi) {
        cout << "-1\n";
    } else if(findlo != lo) {
        cout << lo << '\n';
    } else if(findhi != hi) {
        cout << hi << '\n';
    } else {
        for(int i = lo; i <= hi; i++) {
            cout << i << '\n';
        }
    }
    
    return 0;
}
