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

//Meta Hacker Cup 2025 Round 1 - D

//consider the transition from 'A' to 'B' : '...AAABBB...'
//let there be x 'A's and y 'B's contiguously before and after the transition. 
//if alice chooses one of the min(x, y) 'A's closest to the transition, then bob can just mirror alice's choice and win. 
//if bob chooses one of the min(x, y) 'B's closest to the transition, then alice can just mirror bob's choice and win. 

//so since neither player can actually choose these, then they are effectively removed from the game, 
//and actually we can remove these min(x, y) closest 'A's and 'B's and the outcome of the game will not change. 

//after we remove all A -> B transitions, then the resulting array will look like '...BBAA...' If there exists an 'A' at the end
//of the string, then alice can just choose that one and win. 

bool dfs(int l, int r, vector<vvb>& dp, vector<vvb>& v, bool alice_turn, string& s) {
    if(v[alice_turn][l][r]) {
        return dp[alice_turn][l][r];
    }
    bool ans = false;
    if(alice_turn) {
        if(l == r) {
            //alice lost
            ans = false;
        }
        else {
            ans = false;
            for(int i = l; i < r; i++) {
                if(s[i] == 'A') {
                    if(dfs(i + 1, r, dp, v, !alice_turn, s)) {
                        if(l == 0 && r == s.size()) {
                            // cout << "ALICE MOVE : " << s.substr(i + 1) << "\n";
                        }
                        ans = true;
                        break;
                    }
                }
            }
        }
    }
    else {
        if(l == r) {
            //alice won
            ans = true;
        }
        else {
            ans = false;
            for(int i = l; i < r; i++) {
                if(s[i] == 'B') {
                    ans |= !dfs(l, i, dp, v, !alice_turn, s);
                }
            }
            ans = !ans;
        }
    }
    v[alice_turn][l][r] = true;
    dp[alice_turn][l][r] = ans;
    return ans;
}

bool solve_slow(string& s) {
    int n = s.size();
    vector<vvb> dp(2, vvb(n + 1, vb(n + 1, 0))), v(2, vvb(n + 1, vb(n + 1, 0)));
    return dfs(0, n, dp, v, true, s);
}

bool solve_josh(string& s) {
    int cur = 0;
    for(char c : s) {
        if(c == 'A') {
            cur++;
        } else {
            cur = max(cur - 1, 0);
        }
    }
    return cur;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    int n;
    cin >> n;
    int cnt = 0;
    while(1) {
        cnt ++;
        if(cnt % 1000 == 0) cout << "CNT : " << cnt << endl;
        string s;
        for(int i = 0; i < n; i++) {
            if(rand() % 2) s.push_back('A');
            else s.push_back('B');
        }
        s[0] = 'A';
        s[n - 1] = 'B';
        bool ans = solve_slow(s);
        bool ans_josh = solve_josh(s);
        // cout << s << " " << (ans? "Alice" : "Bob") << std::endl;
        if(ans != ans_josh) {
            cout << s << endl;
            assert(false);
        }
    }

    // int t;
    // cin >> t;
    // int casi = 0;
    // while(t--) {
    //     casi ++;
    //     int n;
    //     cin >> n;
    //     string s;
    //     cin >> s;
    //     bool ans = solve(s);
    //     cout << "Case #" << casi << ": " << (ans? "Alice" : "Bob") << "\n";
    // }
    
    return 0;
}