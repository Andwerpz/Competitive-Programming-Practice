#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - thanosthehero

//just make into strictly increasing sequence. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll ans = 0;
    ll prev = a[n - 1];
    for(int i = n - 2; i >= 0; i--){
        if(prev == 0){
            cout << "1\n";
            return 0;
        }
        if(a[i] > prev - 1){
            ans += a[i] - (prev - 1);
        }
        prev = min((ll) a[i], prev - 1);
    }
    cout << ans << "\n";
    
    return 0;
}
