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

//Codeforces - 2045C

//it's possible to create an interesting abbreviation if there exists a letter that appears in s and is not the first letter in s
//and appears in t and is not the last letter in t. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s, t;
    cin >> s >> t;
    vi p(26, -1);
    for(int i = 0; i < t.size() - 1; i++){
        p[t[i] - 'a'] = i;
    }
    string ans = "";
    int ind = -1, mn_len = 1e9;
    for(int i = 1; i < s.size(); i++) {
        if(p[s[i] - 'a'] == -1) continue;
        int clen = i + (t.size() - p[s[i] - 'a']);
        if(clen < mn_len) mn_len = clen, ind = i;
    }
    if(ind != -1) ans = s.substr(0, ind) + t.substr(p[s[ind] - 'a']);
    cout << (ans.size() == 0? "-1" : ans) << "\n";
    
    return 0;
}