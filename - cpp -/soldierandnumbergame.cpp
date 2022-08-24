#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 546D

//don't use 'endl' use '\n' instead.

//for each number, calculate the amount of factors it has. The amount of factors is equal to the amount of
//times it can be divided by a number greater than 1. 

//since we are doing factorials, we can just take a prefix sum of this array. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    vector<int> dp(5000010, 0);
    for(int i = 1; i < dp.size(); i++) {
        for(int j = i * 2; j < dp.size(); j += i){
            dp[j] = max(dp[j], dp[i] + 1);
        }
    }
    //take pfx sum
    for(int i = 1; i < dp.size(); i++){
        dp[i] += dp[i - 1];
    }
    while(t-- > 0){
        int a, b;
        cin >> a >> b;
        int ans = dp[a] - dp[b];
        cout << ans << "\n";
    }
    
    return 0;
}
