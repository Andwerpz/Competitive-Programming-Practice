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

//Codeforces - 2092B

//each 'zigzag' is going to be a component. Just make sure there aren't too many 1s in each component. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;
        bool ans = true;
        int tcnt = 0, bcnt = 0;
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                if(s[i] == '1') tcnt ++;
            }
            else {
                if(t[i] == '0') bcnt ++;
            }
        }
        if(tcnt > bcnt) ans = false;
        tcnt = 0, bcnt = 0;
        for(int i = 0; i < n; i++){
            if(i % 2 == 1){
                if(s[i] == '1') tcnt ++;
            }
            else {
                if(t[i] == '0') bcnt ++;
            }
        }
        if(tcnt > bcnt) ans = false;
        cout << (ans? "YES" : "NO") << "\n";
    }    
    
    return 0;
}