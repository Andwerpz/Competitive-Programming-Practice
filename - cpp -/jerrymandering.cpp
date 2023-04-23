#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest J

//we can use 3 state dp, n^2 * q. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    while(q-- > 0){
        string query;
        cin >> query;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(query.size() + 1, 1e9)));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dp[i][j][0] = 0;
            }
        }
        for(int i = 0; i < query.size(); i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    if(query[i] != a[j][k]) {
                        dp[j][k][i] ++;
                    }
                    for(int l = 0; l < 4; l++){
                        int nr = j + dr[l];
                        int nc = k + dc[l];
                        if(nr < 0 || nc < 0 || nr >= n || nc >= n){
                            continue;
                        }
                        dp[nr][nc][i + 1] = min(dp[nr][nc][i + 1], dp[j][k][i]);
                    }
                }
            }
        }
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                ans = min(ans, dp[i][j][query.size()]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
