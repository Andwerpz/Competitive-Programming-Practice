
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1636

//just implement dp right lol

//we want to construct all the ordered sets that sum up to x. 

//since the sets have to be ordered, all we have to do is make sure that once we add a certain coin to the dp
//arr, we never add it again. Note that we can add the same coin multiple times, so when doing dp state updates, 
//go in ascending order.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    vector<int> nums(n);
    vector<ll> dp(x + 1);
    ll mod = 1e9 + 7;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    dp[0] = 1;
    for(int i = 0; i < n; i++){
        int next = nums[i];
        for(int j = 0; j <= x - next; j++){
            dp[j + next] += dp[j];
            while(dp[j + next] >= mod){
                dp[j + next] -= mod;
            }
        }
    }
    cout << dp[x] << endl;
    
    return 0;
}
