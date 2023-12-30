#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1896A

//intuitively, we can sort any permutation because we can always force the greatest element to the 
//last position. 

//but, note that we cannot move any element that starts in the first, position, so the correct answer
//is that we can sort any permutation where '1' is in the first position. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        cout << (a[0] == 1? "YES" : "NO") << "\n";
    }
    
    return 0;
}
