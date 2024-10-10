#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - safe

int ans = 1e9;
void solve(vector<vector<int>>& g, int p_moves, int ind) {
    if(ind == 9){
        bool is_valid = true;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(g[i][j] != 0){
                    is_valid = false;
                }
            }
        }
        if(is_valid){
            ans = min(ans, p_moves);
        }
        return;
    }
    for(int move = 0; move < 4; move++){
        solve(g, p_moves + move, ind + 1);
        //apply move
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(i == ind / 3 || j == ind % 3){
                    g[i][j] = (g[i][j] + 1) % 4;
                }
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> g(3, vector<int>(3, 0));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cin >> g[i][j];
        }
    }
    solve(g, 0, 0);
    cout << (ans == 1e9? -1 : ans) << "\n";
    
    return 0;
}
