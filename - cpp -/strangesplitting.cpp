#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984A

//first, if all the elements are the same, then it's impossible to do. 
//otherwise, we can just paint the second element red, and all the other elements blue. This way, the red element will have 
//a range of 0, and the blue elements will have a nonzero range. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n == 2){
            cout << "NO\n";
            continue;
        }
        if(a[0] == a[n - 1]) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << (i == 1? "R" : "B");
        }
        cout << "\n";
    }
    
    return 0;
}