#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC 03-01-24 Div.2 - C

//just brute force all centers. palindromes are at most 26 * 2 characters wide

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int ans = 0;
    int n = s.size();
    for(int i = 0; i < n; i++){
        vector<int> c_cnt(26, 0);
        int l = i - 1;
        int r = i + 1;
        c_cnt[s[i] - 'a'] ++;
        ans ++;
        while(l >= 0 && r < n && s[l] == s[r] && c_cnt[s[l] - 'a'] == 0) {
            c_cnt[s[l] - 'a'] ++;
            ans ++;
            l --;
            r ++;
        }
    }
    for(int i = 0; i < n - 1; i++){
        vector<int> c_cnt(26, 0);
        int l = i;
        int r = i + 1;
        while(l >= 0 && r < n && s[l] == s[r] && c_cnt[s[l] - 'a'] == 0) {
            c_cnt[s[l] - 'a'] ++;
            ans ++;
            l --;
            r ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
