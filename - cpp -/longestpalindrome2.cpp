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

//CSES - 1111

//manacher check. 

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

//returns an array that gives for each element, the max size odd length palindrome centered at that element. 
//note that the string is internally padded, for example 'abcde' will become 'a#b#c#d#e'. 
//this is so even length palindromes can be treated the same way as odd ones. 
vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    vector<int> ans = vector<int>(begin(res) + 1, end(res) - 1);
    for(int i = 0; i < ans.size(); i++){
        ans[i] = ans[i] * 2 - 1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    vi m = manacher(s);
    int mxl = -1;
    int n = s.size();
    for(int i = 0; i < m.size(); i++){
        int len = m[i];
        if(i % 2 == 0){
            len = ((len - 2) + 1) / 2;
        }
        else {
            if(len == 1){
                len = 0;
            }
            else {
                len = len / 2;
            }
        }
        mxl = max(mxl, len);
    }
    for(int i = 0; i < m.size(); i++){
        int len = m[i];
        if(i % 2 == 0){
            len = ((len - 2) + 1) / 2;
        }
        else {
            if(len == 1){
                len = 0;
            }
            else {
                len = len / 2;
            }
        }
        if(len == mxl){
            int l, r;
            if(i % 2 == 0){
                int c = i / 2;
                l = c - (len / 2);
                r = c + (len / 2) + 1;
            }
            else {
                int c = (i + 1) / 2;
                l = c - (len / 2);
                r = c + (len / 2);
            }
            cout << s.substr(l, r - l) << "\n";
            break;
        }
    }
    
    return 0;
}