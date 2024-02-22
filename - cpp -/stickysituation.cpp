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
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    bool is_valid = false;
    for(int i = 0; i < a.size() - 2; i++){
        if(a[i + 0] + a[i + 1] > a[i + 2]) {
            is_valid = true;
        }
    }
    cout << (is_valid? "possible" : "impossible") << "\n";
    
    return 0;
}
