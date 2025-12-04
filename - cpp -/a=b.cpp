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

//Mines HSPC 2025 Open Division - B

//just simulate it lol. You can do everything naively, the constraints are small enough.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<pair<string, string>> r(n);
    for(int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        for(int j = 0; j < tmp.size(); j++) {
            if(tmp[j] == '=') {
                r[i].first = tmp.substr(0, j);
                r[i].second = tmp.substr(j + 1);
                break;
            }
        }
    }
    int cnt = 0;
    while(true) {
        cnt ++;
        int opind = -1, sind = -1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j + r[i].first.size() <= s.size(); j++){
                // cout << "CHECK : " << i << " " << j << "\n";
                if(s.substr(j, r[i].first.size()) == r[i].first) {
                    opind = i, sind = j;
                    goto found;
                }
            }
        }
        found: {}
        if(opind == -1) {
            cout << s << "\n";
            break;
        }
        if(cnt > 5000) {
            cout << "Time Limit Exceeded\n";
            break;
        }
        // cout << "OP : " << s << " " << r[opind].first << " = " << r[opind].second << "\n";
        s = s.substr(0, sind) + r[opind].second + s.substr(sind + r[opind].first.size());
        if(s.size() > 255) {
            cout << "Memory Limit Exceeded\n";
            break;
        }
    }
    
    return 0;
}