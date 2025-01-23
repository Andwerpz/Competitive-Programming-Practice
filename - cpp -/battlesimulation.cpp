#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Kattis - battlesimulation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    string ans = "";
    // reverse(s.begin(), s.end());
    for(int i = 0; i < s.size();){
        if(s.size() - i >= 3 && s[i] != s[i + 1] && s[i + 1] != s[i + 2] && s[i + 2] != s[i]) ans.push_back('C'), i += 3;
        else if(s[i] == 'R') ans.push_back('S'), i ++;
        else if(s[i] == 'B') ans.push_back('K'), i ++;
        else ans.push_back('H'), i ++;
    }
    // reverse(ans.begin(), ans.end());
    cout << ans << "\n";
    
    return 0;
}