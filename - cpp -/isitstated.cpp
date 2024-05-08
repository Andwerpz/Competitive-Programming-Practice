#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1952B

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        bool is_valid = false;
        for(int i = 0; i < s.size() - 1; i++){
            if(s[i] == 'i' && s[i + 1] == 't') {
                is_valid = true;
            }
        }
        cout << (is_valid? "YES\n" : "NO\n");
    }
    
    return 0;
}
