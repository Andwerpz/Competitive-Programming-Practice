#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 07 E

//two state dp. The twist is that you can move backwards. 
//this means that you have to consider the indices in reverse order. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<ll>> dp(n, vector<ll>(n, 1e9));
    dp[0][0] = 0;
    for(int i = 0; i < dp.size(); i++){ //move amt
        for(int j = dp[0].size() - 1; j >= 0; j--){ //which cell
            //forward
            if(j + (i + 1) < n) {
                dp[i + 1][i + j + 1] = min(dp[i + 1][i + j + 1], dp[i][j] + a[j + (i + 1)]); 
            }
            //backwards
            if(j - i >= 0 && i != 0){
                dp[i][j - i] = min(dp[i][j - i], dp[i][j] + a[j - i]);
            }
            //cout << dp[i][j] << " ";
        }
        //cout << "\n";
    }
    ll ans = 1e9;
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[i][n - 1]);
    }
    cout << ans << "\n";
    
    return 0;
}
