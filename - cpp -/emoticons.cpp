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

//2024 NA Mid Central Regional - F

//implementation

vector<string> e = {":)", ":-)", ":-(", ";-)", "xD", "^_^", "-_-", "^o^", "^^;", "(..)"};
int calc_len(string s) {
    int ptr = 0;
    int ans = 0;
    for(;ptr < s.size();){
        int incamt = 1;
        for(int j = 0; j < e.size(); j++){
            if(s.size() - ptr < e[j].size()) {
                continue;
            }
            if(s.substr(ptr, e[j].size()) == e[j]) {
                incamt = e[j].size();
                break;
            }
        }
        ptr += incamt;
        ans ++;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string dict = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";
    string s;
    getline(cin, s);
    int mn_len = 1e9;
    int mx_len = -1;
    for(int i = 0; i < dict.size(); i++){
        for(int j = 0; j < dict.size(); j++){
            string tmp = s;
            for(int k = 0; k < s.size(); k++){
                if(tmp[k] == dict[i]){
                    tmp[k] = dict[j];
                }
            }
            int clen = calc_len(tmp);
            mn_len = min(mn_len, clen);
            mx_len = max(mx_len, clen);
        }
    }
    cout << mn_len << " " << mx_len << "\n";
    
    return 0;
}