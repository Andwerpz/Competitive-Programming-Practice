#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ABC240D

//ideally, you would want to evenly distribute the cooking time between both ovens, but this is not always possible. 
//so, we want to generate all possible cooking times for one oven, and the remaining cooking time is going into the
//other oven. Then, minimize the maximum cooking time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    vector<bool> dp(2e5, false);
    dp[0] = true;
    for(int i = 0; i < n; i++){
        for(int j = dp.size() - 1; j >= 0; j--){
            if(!dp[j]) {
                continue;
            }
            int next = j + a[i];
            if(next < dp.size()) {
                dp[next] = true;
            }
        }
    }
    int ans = 1e9;
    for(int i = 0; i < dp.size(); i++){
        if(!dp[i]) {
            continue;
        }
        ans = min(ans, max(i, sum - i));
    }
    cout << ans << "\n";
    
    return 0;
}
