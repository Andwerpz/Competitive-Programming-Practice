#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1891A

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        bool is_valid = true;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n - 1; i++){
            int ind = i + 1;
            if(__builtin_popcount(ind) == 1) {
                continue;
            }
            if(a[i] > a[i + 1]) {
                is_valid = false;
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}
