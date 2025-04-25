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

//University of Alberta Programming Contest 2025 Open - A

//just check diff against 'UAPC'

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    string t = "UAPC";
    string ans = "";
    int ptr = 0;
    for(int i = 0; i < 4; i++){
        if(ptr == s.size() || s[ptr] != t[i]) ans.push_back(t[i]);
        else ptr ++;
    }
    cout << ans << "\n";
    
    return 0;
}