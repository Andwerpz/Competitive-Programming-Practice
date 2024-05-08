#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - M

//implementation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, l, q;
    cin >> n >> l >> q;
    map<string, string> dict, rdict;
    for(int i = 0; i < n; i++){
        string a, sep, b;
        cin >> a >> sep >> b;
        dict[b] = a;
        rdict[a] = b;
    }
    vector<string> span(l);
    for(int i = 0; i < l; i++){
        cin >> span[i];
        if(span[i] != "???") {
            span[i] = dict[span[i]];
        }
        // cout << "! : " << span[i] << " ";
    }
    // cout << "\n";
    for(int i = 0; i < q; i++){
        bool is_valid = true;
        for(int j = 0; j < l; j++) {
            string next;
            cin >> next;
            if(span[j] == "???") {
                if(rdict.count(next)) {
                    is_valid = false;
                }
            }
            else {
                if(next != span[j]) {
                    is_valid = false;
                }
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}
