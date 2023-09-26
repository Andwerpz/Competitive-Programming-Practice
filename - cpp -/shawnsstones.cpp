#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 D

//adversarial game dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    //i : num remaining stones, j : is it taro's turn
    //val : will taro win
    vector<vector<bool>> dp(k + 1, vector<bool>(2, false));  
    for(int i = 0; i <= k; i++){
        dp[i][0] = true;
        dp[i][1] = false;
        for(int j = 0; j < n; j++){
            int next = i - a[j];
            if(next < 0){
                continue;
            }
            if(dp[next][0]) {
                dp[i][1] = true;
            }
            if(!dp[next][1]) {
                dp[i][0] = false;
            }
        }   
    }
    cout << (dp[k][1]? "First\n" : "Second\n");

    return 0;
}
