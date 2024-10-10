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

//Calgary 2022 - E

//implementation. Find if a bijection exists. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string a;
    cin >> a;
    string line;
    getline(cin, line);
    getline(cin, line);
    vector<string> b(0);
    for(int i = 0; i < line.size();){
        int r = i;
        while(r != line.size() && line[r] != ' '){
            // cout << "INC R : " << r << endl;
            r ++;
        }
        b.push_back(line.substr(i, r - i));
        // cout << "WORD : " << line.substr(i, r - i) << "\n";
        i = r + 1;
    }
    if(a.size() != b.size()) {
        cout << "False\n";
        return 0;
    }
    map<char, string> m;
    for(int i = 0; i < a.size(); i++){
        if(!m.count(a[i])) {
            m[a[i]] = b[i];
        }
        if(m[a[i]] != b[i]) {
            cout << "False\n";
            return 0;
        }
    }
    map<string, char> rm;
    for(int i = 0; i < a.size(); i++){
        if(!rm.count(b[i])) {
            rm[b[i]] = a[i];
        }
        if(rm[b[i]] != a[i]) {
            cout << "False\n";
            return 0;
        }
    }
    cout << "True\n";
    
    return 0;
}