#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1943B

//if for a string S, [l, r) and [l + 1, r + 1) are both palindromes, this tells us that
//  if r - l is even, all the characters in the range are the same
//  else r - l is odd, and every other character in the range is the same. 

//if every character is the same, then it cannot be k good for any value of k (except 1). 
//if only every other character is the same, it cannot be k good for any odd k (except 1). 

//note that you'll still have to check the palindrome that spans the entire substring. 

//to quickly determine if a substring is a palindrome, we can use manacher's algorithm. 

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

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

bool is_pal(int l, int r, vector<int>& p) {
    r --;
    l *= 2;
    r *= 2;
    int mid = (l + r) / 2;
    return p[mid] >= mid - l + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> p = manacher(s);
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            l --;
            ll len = r - l;
            ll ans = len * (len + 1) / 2 - 1;
            bool b_odd = false;
            bool b_even = false;
            if(is_pal(l, r, p)) {
                ans -= len;
            }
            if(is_pal(l, r - 1, p) && is_pal(l + 1, r, p)) {
                b_odd |= len % 2 == 0;
                b_even |= len % 2 == 1;
            }
            if(len != 1 && is_pal(l, r - 2, p) && is_pal(l + 1, r - 1, p) && is_pal(l + 2, r, p)) {
                b_odd |= len % 2 == 1;
                b_even |= len % 2 == 0;
            }
            ll even_sum = (len / 2) * ((len / 2) + 1);
            ll odd_sum = len * (len + 1) / 2 - 1 - even_sum;
            even_sum -= len * (len % 2 == 0);
            odd_sum -= len * (len % 2 == 1);
            ans -= even_sum * b_even + odd_sum * b_odd;
            cout << ans << "\n";
        }
    }
    
    return 0;
}
