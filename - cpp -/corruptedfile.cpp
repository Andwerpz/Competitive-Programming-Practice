#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//2025 ICPC Asia Pacific Championship - G

//think about working backwards. Starting from t, we can insert '1' anywhere, but a '0' can only be inserted into 
//a position that is already adjacent to a '0'. Then, some s can turn into a t iff we can turn t into s by following 
//these insertions. 

//we can determine if we can turn t into s using 2ptrs. Look at code for details. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int _t;
    cin >> _t;
    while(_t--){
        int n, m;
        cin >> n >> m;
        string s, t;
        cin >> s >> t;
        int zs = 0, zt = 0;
        for(int i = 0; i < n; i++) zs += s[i] == '0';
        for(int i = 0; i < m; i++) zt += t[i] == '0';
        if(zt > zs) {
            cout << "no\n";
            continue;
        }
        bool is_valid = true;
        int tptr = 0;
        int mr0 = -1;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') {
                if(tptr != m && t[tptr] == '1') {
                    //consume '1' in t
                    tptr ++;
                }
                else {
                    //do nothing, just add '1' in t
                }
            }
            else {
                if(tptr != m && t[tptr] == '0') {
                    //consume '0' in t
                    tptr ++;
                    mr0 = tptr;
                }
                else if(tptr != 0 && t[tptr - 1] == '0' && zt < zs) {
                    //insert '0' in t
                    zt ++;
                }
                else {
                    //it's possible to account for this '0', just have to move tptr back to most recent '0'
                    if(mr0 == -1) {
                        //no way to account for this '0'
                        is_valid = false;
                        break;
                    }
                    tptr = mr0;
                }
            }
        }
        //need to consume everything in t
        if(tptr != m) is_valid = false;
        cout << (is_valid? "yes" : "no") << "\n";
    }
    
    return 0;
}