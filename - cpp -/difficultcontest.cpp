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

//Codeforces - 2125A

//if you put all the 'T's in front, then 'FF' and 'N' will never get the chance to form the hard combinations. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        vi f(26, 0);
        string s;
        cin >> s;
        int n = s.size();
        for(int i = 0; i < n; i++){
            f[s[i] - 'A'] ++;
        }
        for(int i = 0; i < f['T' - 'A']; i++) cout << 'T';
        for(int i = 0; i < 26; i++){
            if(i == 'T' - 'A') continue;
            for(int j = 0; j < f[i]; j++) cout << (char) ('A' + i);
        }
        cout << "\n";
    }
    
    return 0;
}