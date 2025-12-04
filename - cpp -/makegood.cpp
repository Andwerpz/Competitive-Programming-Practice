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

//Codeforces - 2143E

//nice observation problem. 
//good to be thorough when generating testcases. 

//first, observe that even blocks of like brackets can be absorbed into adjacent blocks. So we can always convert the 
//bracket string into either a collection of odd length blocks, or one big even length block. 
//the one even length block case is easy to solve, we're more interested in the multiple odd length block case. 

//next, observe that any pair of like brackets can 'move' to wherever they want. Of course, the brackets themselves are
//not moving, but it's as if they moved. So then every odd length block will turn into a single bracket, so we'll have
//a collection of alternating brackets, plus a bunch of free-floating pairs of brackets. 

//finally, all we have to do is see if we can place the pairs in such a way as to make a valid bracket sequence.
//we just have to do some casework with this. 

//in order to extract the odd length blocks and number of free-floating pairs, we can just use a stack. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int pcnt = 0;
        {   
            stack<char> stk;
            for(int i = 0; i < n; i++) {
                if(stk.size() != 0 && s[i] == stk.top()) {
                    stk.pop();
                    pcnt ++;
                }
                else stk.push(s[i]);
            }
            s = "";
            while(stk.size() != 0) {
                s.push_back(stk.top());
                stk.pop();
            }
            reverse(s.begin(), s.end());
            n = s.size();
        }
        int l = 0, r = 0, cur = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '(') cur ++;
            else cur --;
            l = min(l, cur);
        }
        l *= -1;
        cur = 0;
        reverse(s.begin(), s.end());
        for(int i = 0; i < n; i++) {
            if(s[i] == ')') cur ++;
            else cur --;
            r = min(r, cur);
        }
        r *= -1;
        reverse(s.begin(), s.end());
        // cout << "LR : " << l << " " << r << " " << pcnt << "\n";
        // cout << "S : " << s << "\n";
        if((l % 2) != (r % 2)) {
            cout << "-1\n";
            continue;
        }
        if(l % 2) l ++;
        if(r % 2) r ++;
        if((l + r) / 2 > pcnt) {
            cout << "-1\n";
            continue;
        }
        if((pcnt - (l + r) / 2) % 2) {
            cout << "-1\n";
            continue;
        }
        int half = pcnt - (l + r) / 2;
        l += half;
        r += half;
        string ans = "";
        for(int i = 0; i < l; i++) ans.push_back('(');
        ans += s;
        for(int i = 0; i < r; i++) ans.push_back(')');
        cout << ans << "\n";
    }
    
    return 0;
}