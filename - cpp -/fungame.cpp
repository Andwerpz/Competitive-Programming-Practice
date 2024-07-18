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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1994B

//note that you can change any element after the first element that is equal to '1' in s. Therefore, before the first
//element equal to '1', s and t must match. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;
        bool is_valid = true;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '1') {
                break;
            }
            if(s[i] != t[i]){
                is_valid = false;
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}