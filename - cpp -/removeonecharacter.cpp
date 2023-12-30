#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC130A

//if you remove two letters from the same contiguous section of same letters, then the result 
//string should be identical. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int r = i;
        while(r != n && s[r] == s[i]) {
            r ++;
        }
        ll dist = r - i;
        ans += dist * (dist - 1) / 2;
        i = r - 1;
    }
    cout << ans << "\n";
    
    return 0;
}
