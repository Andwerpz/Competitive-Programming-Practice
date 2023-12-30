#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1917B

//you can make each suffix start with any letter that appears before it. 
//so you just have to go through the string, and for each suffix, count the number of unique letters in front of it. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        set<char> st;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            st.insert(s[i]);
            ans += st.size();
        }
        cout << ans << "\n";
    }
    
    return 0;
}
