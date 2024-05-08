#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1948A

//note that special characters are always on the 'ends' of substrings of contiguous same characters. 
//also note that the number of special characters in a string has to be even, due to the above. 

//so, if n is even, we can always make a string, otherwise it's impossible. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n % 2 == 1){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for(int i = 0; i < n / 2; i++){
            char c = 'A' + (i % 10);
            cout << c << c;
        }
        cout << "\n";
    }
    
    return 0;
}
