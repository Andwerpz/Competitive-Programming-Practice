#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1948B

//we can solve greedily. Go from right to left, and if we see any number that is out of order, we have to split it. 
//if the final array is out of order, it's impossible. 

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
        int ptr = -1;
        for(int i = n - 2; i >= 0; i--){
            if(a[i] > a[i + 1]) {
                ptr = i;
                break;
            }
        }
        vector<int> b(0);
        for(int i = 0; i < n; i++){
            if(i > ptr) {
                b.push_back(a[i]);
                continue;
            }
            string s = to_string(a[i]);
            for(int j = 0; j < s.size(); j++){
                b.push_back(s[j] - '0');
            }
        }
        bool is_valid = true;
        for(int j = 0; j < b.size() - 1; j++){
            is_valid = is_valid && (b[j] <= b[j + 1]);
        }
        cout << (is_valid? "YES\n" : "NO\n");
    }
    
    return 0;
}
