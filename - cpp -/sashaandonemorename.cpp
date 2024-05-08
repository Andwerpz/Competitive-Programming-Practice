#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1109B

//if it's possible, then you can always do it in 2 cuts or less. 

//let's say that |s| % 2 == 0. Then with 2 cuts, the only case that it's not possible is if the entire string
//is the same character, in which case it's not possible with any amount of cuts. 

//now, in what case is it possible to do with just one cut. 
//as an example, "abba" is possible to do with 1 cut, and we can notice this is because 
//1. |"abba"| % 2 == 0
//2. "ab" != "ba", or the first half doesn't equal the second half. 

//notice that "abbaabba" is also possible to do with 1, we just cut it into "ab" and "baaabba". 

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
    
    string s;
    cin >> s;
    vector<int> m = manacher(s);
    bool imposs = true;
    for(int i = 0; i < s.size() / 2; i++){
        imposs &= is_palindrome(0, i + 1, m);
    }
    if(imposs) {
        cout << "Impossible\n";
        return 0;
    }
    bool poss = false;
    int ptr = s.size();
    while(ptr % 2 == 0){
        ptr /= 2;
        if(!is_palindrome(0, ptr, m)) {
            poss = true;
            break;
        }
    }
    cout << 2 - poss << "\n";
    
    return 0;
}
