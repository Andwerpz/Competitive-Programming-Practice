#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

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