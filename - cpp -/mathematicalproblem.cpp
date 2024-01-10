#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1916D

//first, we can do some brute force simulation to find a pattern. We can generate all perfect
//squares of a certain length, then sort the digits of each number in alphabetical order. Finally, 
//sort the numbers in lexicographical order. 

//you should end up seeing numbers like 0000169 or 00169; an even amount of 0s followed by '169', and 
//if n >= 3, then you should see at least n + 1 of them. 

//from here, you can notice:
//13^2 = 169, 103^2 = 10609, 1003^2 = 1006009
//31^2 = 961, 301^2 = 90601, 3001^2 = 9006001
//14^2 = 196, 140^2 = 19600, 1400^2 = 1960000
//we can use this to construct the answer.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        // vector<string> a(0);
        // for(int i = 1; i < 100000; i++){
        //     int sq = i * i;
        //     string s = to_string(sq);
        //     if(s.size() == n){
        //         sort(s.begin(), s.end());
        //         if(s == "000000169") {
        //             cout << sq << "\n";
        //         }
        //         a.push_back(s);
        //     }
        // }
        if(n == 1){
            cout << "1\n";
            continue;
        }
        vector<string> ans(0);
        for(int i = 0; i < n / 2; i++){
            int gap = i + 1;
            {
                string s(n, '0');
                s[0] = '1';
                s[gap] = '6';
                s[gap * 2] = '9';
                ans.push_back(s);
            }
            {
                string s(n, '0');
                s[0] = '9';
                s[gap] = '6';
                s[gap * 2] = '1';
                ans.push_back(s);
            }
        }
        string s(n, '0');
        s[0] = '1';
        s[1] = '9';
        s[2] = '6';
        ans.push_back(s);
        for(int i = 0; i < n; i++){
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
