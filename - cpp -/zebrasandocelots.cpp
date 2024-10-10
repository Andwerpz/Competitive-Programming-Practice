#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - zebrasocelots

//interpret the zebras and ocelots as a binary number, Z = 0, O = 1
//conveniently, Zero = 0, One = 1

//then, each time the bell tolls, we are effectively subtracting 1

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<bool> a(n);
    for(int i = 0; i < n; i++){
        char c;
        cin >> c;
        a[i] = c == 'O';
    }
    reverse(a.begin(), a.end());
    ll ans = 0;
    ll p = 1;
    for(int i = 0; i < n; i++){
        ans += p * a[i];
        p *= 2;
    }
    cout << ans << "\n";
    
    return 0;
}
