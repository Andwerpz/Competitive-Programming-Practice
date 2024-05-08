#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1951E

//i assume that's if it's possible to partition the string, it's possible to do it with only splitting the string
//at most once. 

//if it's impossible to do so, then it means that for every prefix + suffix pair, at least one of them must be a 
//palindrome. 

//assuming that |s| is sufficiently large (>= 10 or so), we can do the following analysis. 
//if |s| is even, then this implies all the characters in s are the same. 
//if |s| is odd, then this implies that all the characters in s are either the same, or alternating. 

//this means that if it's impossible to split into two parts, then it will be impossible to split using more than 
//two parts. 

//So, for each string split, i just try it to see if it works. To try each split in constant time, I precompute
//all the palindromes using manacher. 

//to handle small |s|, i just try the case where we pick the entire string. 

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

bool is_palindrome(int l, int r, vector<int>& m) {  //[l, r)
    l *= 2;
    r --;
    r *= 2;
    return m[(r + l) / 2] >= r - l + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());
        if(s != rev) {
            cout << "YES\n";
            cout << "1\n";
            cout << s << "\n";
            continue;
        }
        vector<int> m = manacher(s);
        bool is_valid = false;
        for(int i = 1; i < n; i++){
            if(!is_palindrome(0, i, m) && !is_palindrome(i, n, m)) {
                is_valid = true;
                cout << "YES\n";
                cout << "2\n";
                cout << s.substr(0, i) << " " << s.substr(i) << "\n";
                break;
            }
        }
        if(!is_valid) {
            cout << "NO\n";
        }
    }
    
    return 0;
}
