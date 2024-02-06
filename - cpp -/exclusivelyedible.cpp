#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UVA - 11311

//we can reduce the problem to a nim like game over 4 numbers 

//let
//a = number of cells to the left of chocolate
//b = number of cells to right
//c = number of cells to top
//d = number of cells to bottom

//note that each time you slice, you just subtract some amount from one of a, b, c, d. 
//and once a, b, c, d = 0, the game is over. 
//thus, we can just do 0-1 dp over the entire state-space of a, b, c, d. 

//since a, b, c, d can be at most 50, and each state requires to check around 50 * 4 other states,
//total number of operations is around 50^5 * 4, which is enough to run in time. 

//if it's p1 turn, will he win?
bool solve(int a, int b, int c, int d, vector<vector<vector<vector<bool>>>>& dp, vector<vector<vector<vector<bool>>>>& v) {
    if(v[a][b][c][d]) {
        return dp[a][b][c][d];
    }
    v[a][b][c][d] = true;
    bool can_win = false;
    for(int i = a - 1; i >= 0; i--){
        can_win |= !solve(i, b, c, d, dp, v);
    }
    for(int i = b - 1; i >= 0; i--){
        can_win |= !solve(a, i, c, d, dp, v);
    }
    for(int i = c - 1; i >= 0; i--){
        can_win |= !solve(a, b, i, d, dp, v);
    }
    for(int i = d - 1; i >= 0; i--){
        can_win |= !solve(a, b, c, i, dp, v);
    }
    dp[a][b][c][d] = can_win;
    return can_win;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<vector<vector<bool>>>> dp(50, vector<vector<vector<bool>>>(50, vector<vector<bool>>(50, vector<bool>(50, false))));
    vector<vector<vector<vector<bool>>>> v(50, vector<vector<vector<bool>>>(50, vector<vector<bool>>(50, vector<bool>(50, false))));
    int t;
    cin >> t;
    while(t--){
        int m, n, row, col;
        cin >> m >> n >> row >> col;
        int a = row;
        int b = col;
        int c = m - row - 1;
        int d = n - col - 1;
        cout << (!solve(a, b, c, d, dp, v)? "Hansel" : "Gretel") << "\n";
    }
    
    return 0;
}
