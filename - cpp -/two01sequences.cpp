#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704A

//we can only change the first element of a, the latter n - 1 elements have to match the latter m - 1 elements of
//b exactly. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        bool is_valid = true;
        for(int i = 0; i < m - 1; i++){
            if(a[n - 1 - i] != b[m - 1 - i]) {
                is_valid = false;
            }
        }
        if(!is_valid) {
            cout << "NO\n";
            continue;
        }
        is_valid = false;
        for(int i = 0; i < n - m + 1; i++){
            if(a[i] == b[0]) {
                is_valid = true;
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}