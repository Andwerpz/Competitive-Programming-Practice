#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC 03-01-24 Div.2 - F

//can do bitset dp. 

//each state can be represented as a bitset storing what days you still have available, and
//how many jobs you've considered so far. 

int state_add(int state, int other) {
    for(int i = 0; i < 7; i++){
        int bit = (other >> i) & 1;
        if(bit == 0) {
            continue;
        }
        if(((state >> i) & 1) == 0) {
            state |= (1 << i);
        }
        else if(((state >> (i + 7)) & 1) == 0){
            state |= (1 << (i + 7));
        }
        else {
            return -1;
        }
    }
    return state;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> moves;
    for(int i = 0; i < n; i++){
        int c_move = 0;
        int profit;
        for(int j = 0; j < 7; j++){
            c_move <<= 1;
            int n_bit;
            cin >> n_bit;
            c_move += n_bit;
        }
        cin >> profit;
        moves.push_back({c_move, profit});
        // cout << "MOVE : " << c_move << " " << profit << "\n";
    }
    vector<vector<int>> dp(n + 1, vector<int>((1 << 14), 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < dp[0].size(); j++){
            //do nothing
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            int move = moves[i].first;
            int profit = moves[i].second;
            int n_state = state_add(j, move);
            if(n_state == -1){
                continue;
            }
            dp[i + 1][n_state] = max(dp[i + 1][n_state], dp[i][j] + profit);
        }
    }
    int ans = 0;
    for(int i = 0; i < dp[0].size(); i++){
        ans = max(ans, dp[n][i]);
    }
    cout << ans << "\n";
    
    return 0;
}
