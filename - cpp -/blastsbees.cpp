#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 F

//once you map the square tile (array) to the hexagon tiles described in the problem, it's really easy. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<vector<int>>> dp(15, vector<vector<int>>(100, vector<int>(100, 0)));
    int cx = 50;
    int cy = 50;
    dp[0][cx][cy] = 1;
    vector<int> dr = {-1, -1, 0, 0, 1, 1};
    vector<int> dc = {0, 1, -1, 1, -1, 0};
    for(int i = 0; i < dp.size() - 1; i++){
        for(int j = 0; j < dp[0].size(); j++){
            for(int k = 0; k < dp[0][0].size(); k++){
                for(int l = 0; l < dr.size(); l++){
                    int nr = j + dr[l];
                    int nc = k + dc[l];
                    if(nr < 0 || nr >= dp[0].size() || nc < 0 || nc >= dp[0].size()) {
                        continue;
                    }
                    dp[i + 1][nr][nc] += dp[i][j][k];
                }
            }
        }
    }
    int t;
    cin >> t;
    while(t-- ){
        int n;
        cin >> n;
        cout << dp[n][cx][cy] << "\n";
    }
    
    return 0;
}
