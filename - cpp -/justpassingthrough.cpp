#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 12 D

//3 state dp. i = row, j = col, k = num passes travelled through

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c, n;
    cin >> r >> c >> n;
    vector<vector<vector<ll>>> dp(r, vector<vector<ll>>(c, vector<ll>(n + 1, 1e18)));
    vector<vector<bool>> isPass(r, vector<bool>(c, false));
    vector<vector<ll>> g(r, vector<ll>(c, 0));
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> g[i][j];
        }
    }
    for(int i = 1; i < r - 1; i++){
        for(int j = 1; j < c - 1; j++){
            if(g[i][j - 1] == -1 || g[i][j + 1] == -1 || g[i + 1][j] == -1 || g[i - 1][j] == -1){
                continue;
            }
            if(g[i][j - 1] < g[i][j] && g[i][j + 1] < g[i][j] && g[i + 1][j] > g[i][j] && g[i - 1][j] > g[i][j]){
                isPass[i][j] = true;
            }
        }
    }
    for(int i = 0; i < r; i++){
        if(g[i][0] == -1){
            continue;
        }
        dp[i][0][0] = g[i][0]; 
    }
    vector<int> dr = {-1, 0, 1};
    vector<int> dc = {1, 1, 1};
    for(int i = 0; i <= n; i++){
        for(int k = 0; k < c; k++){
            for(int j = 0; j < r; j++){
                if(g[j][k] == -1){
                    continue;
                }
                for(int l = 0; l < 3; l++){
                    int nr = j + dr[l];
                    int nc = k + dc[l];
                    if(nr < 0 || nc < 0 || nr >= r || nc >= c) {
                        continue;
                    }
                    if(g[nr][nc] == -1){
                        continue;
                    }
                    if(isPass[nr][nc]) {
                        if(i == n){
                            continue;
                        }
                        dp[nr][nc][i + 1] = min(dp[nr][nc][i + 1], dp[j][k][i] + g[nr][nc]);
                    }
                    else {
                        dp[nr][nc][i] = min(dp[nr][nc][i], dp[j][k][i] + g[nr][nc]);
                    }
                }
            }
        }
    }
    bool isValid = false;
    ll ans = 1e18;
    for(int i = 0; i < r; i++){
        if(g[i][c - 1] == -1){
            continue;
        }
        ans = min(ans, dp[i][c - 1][n]);
    }
    if(ans == 1e18){
        cout << "impossible\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}
