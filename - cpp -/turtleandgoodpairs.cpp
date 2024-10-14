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

//Codeforces - 2003C

//if for every letter, the next letter is different, that will always maximize the number of good pairs. 

//we can just greedily maximize the amount of i where s[i] != s[i + 1]. 

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
        vi cnt(26, 0);
        for(int i = 0; i < n; i++){
            cnt[s[i] - 'a'] ++;
        }
        string ans = "";
        priority_queue<pair<int, char>> q;
        for(int i = 0; i < 26; i++){
            if(cnt[i] == 0){
                continue;
            }
            q.push({cnt[i], 'a' + i});
        }
        pair<int, char> held;
        bool has_held = false;
        while(q.size() != 0){
            int camt = q.top().first;
            char cchar = q.top().second;
            q.pop();
            ans.push_back(cchar);
            camt --;
            if(has_held) {
                q.push(held);
            }
            has_held = false;
            if(camt != 0){
                held = {camt, cchar};
                has_held = true;
            }
        }
        if(has_held) {
            for(int i = 0; i < held.first; i++){
                ans.push_back(held.second);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}