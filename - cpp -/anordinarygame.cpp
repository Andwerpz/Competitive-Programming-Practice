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

//AtCoder - ARC64D

//some jank stuff. Josh has a much better solution. 

//The idea is to look at how the string must be at the end. It must be entirely alternating between
//two characters. We can determine the parity of the length of the string at the end of the game
//entirely based off of whether or not the first and last characters match, and use that to
//determine who has to win the game. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    //check if it's currently impossible to move
    bool move_possible = false;
    for(int i = 1; i < n - 1; i++){
        if(s[i - 1] != s[i + 1]) move_possible = true;
    }
    if(!move_possible) {
        cout << "Second\n";
        return 0;
    }
    //check if it's possible to immediately win
    bool im_win = false;
    {
        vi f(26, 0);
        for(int i = 0; i < n; i++){
            f[s[i] - 'a'] ++;
        }
        int ucnt = 0;
        for(int i = 0; i < 26; i++){
            if(f[i]) ucnt ++;
        }
        if(ucnt == 3) {
            int mn_cnt = 1e9;
            int mn_char = -1;
            for(int i = 0; i < 26; i++){
                if(f[i]) {
                    if(f[i] < mn_cnt) {
                        mn_cnt = f[i];
                        mn_char = i;
                    }
                }
            }
            if(mn_cnt == 1) {
                int pos = -1;
                for(int i = 1; i < n - 1; i++){
                    if(s[i] - 'a' == mn_char && s[i - 1] != s[i + 1]) {
                        pos = i;
                    }
                }
                if(pos != -1){
                    im_win = true;
                }
            }
        }
    }
    if(im_win) {
        cout << "First\n";
        return 0;
    }
    //at this point, it's just parity
    if(s[0] == s[n - 1]) n --;
    cout << (n % 2? "First" : "Second") << "\n";

    return 0;
}