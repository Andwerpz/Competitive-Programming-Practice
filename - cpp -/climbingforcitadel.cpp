#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest C 

//two state dp; how far along you are, what equipment you are currently using. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<pair<int, int>> g(m);
    for(int i = 0; i < m; i++){
        string name;
        cin >> name;
        int l, r;
        cin >> l >> r;
        g[i] = {l, r};
    }
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m, 1e9));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            int l = g[j].first;
            int r = g[j].second;
            if(a[i] < l || a[i] > r) {
                dp[i][j] = -1;
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(dp[0][i] == -1){
            continue;
        }
        dp[0][i] = 0;
    }
    for(int i = 0; i < n; i++){
        int minSwitch = 1e9;
        for(int j = 0; j < m; j++){
            if(dp[i][j] == -1){
                continue;
            }
            //don't switch
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            //switch
            minSwitch = min(minSwitch, dp[i][j] + 1);
        }
        for(int j = 0; j < m; j++){
            dp[i + 1][j] = min(dp[i + 1][j], minSwitch);
        }
    }
    int ans = 1e9;
    for(int i = 0; i < m; i++){
        if(dp[n][i] == -1){
            continue;
        }
        ans = min(ans, dp[n][i]);
    }
    cout << ans << "\n";
    
    return 0;
}
