#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984B

//If we add two large digits together, then we're guraranteed to carry. This allows us to make some observations about
//the result of adding two large numbers of equal length.

//1. The most significant digit must be 1; the most significant digits in the two large numbers must carry.
//2. The least significant digit cannot be 9. 
//3. All other digits cannot be 0, since the previous digit carries. 

//as long as the number follows these three, then it should be valid. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        bool is_valid = true;
        if(s[0] != '1'){
            is_valid = false;
        }
        for(int i = 1; i < s.size() - 1; i++){
            if(s[i] == '0') {
                is_valid = false;
            }
        }
        if(s[s.size() - 1] == '9') {
            is_valid = false;
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}