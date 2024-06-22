#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1976A

//conveniently, the password must be in sorted order to be valid. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        string tmp = s;
        sort(s.begin(), s.end());
        cout << (tmp == s? "YES" : "NO") << "\n";
    }
    
    return 0;
}