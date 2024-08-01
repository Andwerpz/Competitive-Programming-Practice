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

//Codeforces - 1997A

//just find any two adjacent characters which are the same, and insert a different character between them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        bool placed = false;
        for(int i = 0; i < s.size(); i++){
            cout << s[i];
            if(!placed) {
                if((i != s.size() - 1 && s[i] == s[i + 1]) || (i == s.size() - 1)) {
                    placed = true;
                    cout << (char) ((s[i] - 'a' + 1) % 26 + 'a');
                }
            }
        }
        cout << "\n";
    }
    
    return 0;
}