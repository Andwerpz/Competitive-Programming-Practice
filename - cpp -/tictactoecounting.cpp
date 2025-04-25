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

//2022 ICPC NAC - J

//implementation. Remember that 'X' and 'O' alternate turns. 

map<int, pii> dp;

int serialize_board(string b) {
    assert(b.size() == 9);
    int res = 0;
    for(int i = 0; i < 9; i++){
        res *= 3;
        res += b[i] == 'X'? 1 : (b[i] == 'O'? 2 : 0);
    }
    return res;
}

//{X wins, O wins}
pii dfs(string b) {
    int id = serialize_board(b);
    if(dp.count(id)) return dp[id];
    //is this a win?
    pii ans = {0, 0};
    char win = 0;
    for(int i = 0; i < 3; i++) {
        if(b[i * 3 + 0] != '.' && b[i * 3 + 0] == b[i * 3 + 1] && b[i * 3 + 1] == b[i * 3 + 2]) win = b[i * 3 + 0];
        if(b[0 * 3 + i] != '.' && b[0 * 3 + i] == b[1 * 3 + i] && b[1 * 3 + i] == b[2 * 3 + i]) win = b[0 * 3 + i];
    }
    if(b[0] != '.' && b[0] == b[4] && b[4] == b[8]) win = b[0];
    if(b[2] != '.' && b[2] == b[4] && b[4] == b[6]) win = b[2];
    if(win != 0) {
        ans = (win == 'X'? make_pair(1, 0) : make_pair(0, 1));
        // cout << "WIN : " << b << "\n";
    }
    else {
        int cnt = 0;
        for(int i = 0; i < 9; i++) cnt += b[i] == 'X'? 1 : (b[i] == 'O'? -1 : 0);
        for(int i = 0; i < 9; i++){
            if(b[i] != '.') continue;
            pii ansx = {0, 0}, anso = {0, 0};
            if(cnt == 0) {
                b[i] = 'X';
                ansx = dfs(b);
            }
            else {
                b[i] = 'O';
                anso = dfs(b);
            }
            b[i] = '.';
            ans.first += ansx.first + anso.first;
            ans.second += ansx.second + anso.second;
        }
    }
    // cout << "VISIT ID : " << id << " " << ans.first << " " << ans.second << "\n";
    dp[id] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    dfs(string(9, '.'));
    // cout << "VISITABLE : " << dp[0].first << " " << dp[0].second << "\n";
    int t;
    cin >> t;
    while(t--){
        string b;
        cin >> b;
        int id = serialize_board(b);
        if(dp.count(id)) {
            cout << dp[id].first << " " << dp[id].second << "\n";
        }
        else cout << "-1 -1\n";
    }
    
    return 0;
}