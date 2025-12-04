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

//Mines HSPC 2025 Open Division - E

//do two passes to simulate the infecting. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int p, t;
    cin >> p >> t;
    string s;
    cin >> s;
    t = (t - 1) / p;
    int ls = 1e9;
    for(int i = 0; i < s.size(); i++){
        ls ++;
        if(s[i] == 'I') {
            ls = 0;
        }
        else if(s[i] == 'W') {
            ls = 1e9;
        }
        else {
            if(ls <= t) s[i] = 'I';
        }
    }
    ls = 1e9;
    for(int i = s.size() - 1; i >= 0; i--){
        ls ++;
        if(s[i] == 'I') {
            ls = 0;
        }
        else if(s[i] == 'W') {
            ls = 1e9;
        }
        else {
            if(ls <= t) s[i] = 'I';
        }
    }
    bool is_valid = false;
    for(int i = 0; i < s.size(); i++) if(s[i] == 'H') is_valid = true;
    cout << (is_valid? "CURED" : "ALL INFECTED") << "\n";
    
    return 0;
}