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

//Mines HSPC 2025 Open Division - K

//this problem sucks to read
//implementation

string parse_ip(string s) {
    vi a(0);
    for(int i = 0; i < s.size(); ) {
        int r = i;
        while(r != s.size() && s[r] != '.' && s[r] != '/') r ++;
        a.push_back(stoi(s.substr(i, r - i)));
        i = r + 1;
    }
    string ans = "";
    for(int i = 0; i < 4; i++){
        for(int j = 7; j >= 0; j--) {
            if(a[i] & (1 << j)) ans.push_back('1');
            else ans.push_back('0');
        }
    }
    if(a.size() == 5) {
        ans = ans.substr(0, a[4]);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a[i] = parse_ip(s);
        // cout << "I : " << i << " " << a[i] << "\n";
    }
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        s = parse_ip(s);
        // cout << "S : " << s << "\n";
        int lpfx = -1, lind = -1;
        for(int j = 0; j < n; j++){
            // cout << "COMP : " << s.substr(0, a[j].size()) << " " << a[j] << " " << (s.substr(0, a[j].size()) == a[j]) << "\n";
            // cout << "LPFX : " << lpfx << " " << a[j].size() << " " << (a[j].size() > lpfx) << "\n";
            if((int) a[j].size() > lpfx && s.substr(0, a[j].size()) == a[j]) {
                // cout << "MATCH : " << "\n";
                lpfx = a[j].size(), lind = j + 1;
            }
        }
        cout << lind << "\n";
    }
    
    return 0;
}