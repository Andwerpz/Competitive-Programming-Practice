#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1915B

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        char ans = '?';
        for(int i = 0; i < 3; i++){
            string s;
            cin >> s;
            set<char> st;
            for(int j = 0; j < 3; j++){
                if(s[j] == '?') {
                    continue;
                }
                st.insert(s[j]);
            }
            for(char j = 'A'; j <= 'C'; j++){
                if(st.find(j) == st.end()) {
                    ans = j;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
