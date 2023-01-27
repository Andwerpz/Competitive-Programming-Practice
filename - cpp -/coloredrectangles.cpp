#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) H

//dp + greedy
//dp is just brute force + greedy isn't it... 
//nah, it's more like smart brute force. Smart Force

//the idea is for each combination of i, j, k, where i denotes the number of red sticks used, j denotes the number
//of blue sticks used, and k denotes the number of green sticks used, figure out the maximum area. 

//in order to do this, we will want to order the pairs of sticks in descending order, and pair the sticks off
//from highest to lowest. idk how this is optimal, but it works, just trust me. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, g, b;
    cin >> r >> g >> b;
    vector<ll> rArr(r);
    vector<ll> gArr(g);
    vector<ll> bArr(b);
    for(int i = 0; i < r; i++){
        cin >> rArr[i];
    }
    for(int i = 0; i < g; i++) {
        cin >> gArr[i];
    }
    for(int i = 0; i < b; i++){
        cin >> bArr[i];
    }
    sort(rArr.begin(), rArr.end(), [](ll a, ll b){return b < a;});
    sort(gArr.begin(), gArr.end(), [](ll a, ll b){return b < a;});
    sort(bArr.begin(), bArr.end(), [](ll a, ll b){return b < a;});
    vector<vector<vector<ll>>> dp(r + 1, vector<vector<ll>>(g + 1, vector<ll>(b + 1, 0)));
    ll ans = 0;
    for(int i = 0; i <= r; i++){
        for(int j = 0; j <= g; j++){
            for(int k = 0; k <= b; k++){
                if(i != r && j != g) {
                    dp[i + 1][j + 1][k] = max(dp[i + 1][j + 1][k], dp[i][j][k] + rArr[i] * gArr[j]);
                }
                if(j != g && k != b){
                    dp[i][j + 1][k + 1] = max(dp[i][j + 1][k + 1], dp[i][j][k] + gArr[j] * bArr[k]);
                }
                if(i != r && k != b){
                    dp[i + 1][j][k + 1] = max(dp[i + 1][j][k + 1], dp[i][j][k] + rArr[i] * bArr[k]);
                }
                ans = max(ans, dp[i][j][k]);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
