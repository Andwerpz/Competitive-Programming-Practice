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

//Codeforces - 2030C

//if there are two 1s in a row, or if there is a 1 on the edge, Alice can always win by surrounding
//a 1 by two 'or's. Otherwise, it's impossible to win, as Bob can just negate any 1 that alice tries to 
//capture. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        if(s[0] == '1' || s[n - 1] == '1'){
            cout << "YES\n";
            continue;
        }
        bool two = false;
        for(int i = 0; i < n - 1; i++){
            if(s[i] == s[i + 1] && s[i] == '1') {
                two = true;
                break;
            }
        }
        cout << (two ? "YES" : "NO") << "\n";
    }
    
    return 0;
}