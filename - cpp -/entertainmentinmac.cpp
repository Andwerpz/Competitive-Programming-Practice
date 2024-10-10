#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1935A

//since n is even, and it's always bad to extend the length of s, the answer is either 
//the original s, or doubled, reversed s. 

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
        string t = s;
        reverse(t.begin(), t.end());
        t += s;
        cout << (t < s? t : s) << "\n";
    }
    
    return 0;
}
