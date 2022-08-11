#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1716D

//notice that the minimum amount of moves, 'm' is (m * (m + 1)) / 2 = n, which comes to around 2 * sqrt(n). 
//we can make a two state dp, where dp[i][j] is the amount of different ways to get to location j with i moves. 

//the problem is that doing the state transitions for dp[i][j] seems like it would take an average of log(n) time 
//due to the requirement that move lengths be a multiple of i + k, something we can't afford with n * sqrt(n) states. 

//to circumvent this, we notice that if we do each move amount, or 'i' in one go, then we can record the moves in an 
//auxillary array, 'mRec' of size i + k, and just tile it down the n positions using the mod operator, meaning we can
//update states in constant time. 

//Since we need n * sqrt(n) memory, storing the entire dp array doesn't work. Luckily, we can observe that to solve the
//entire dp[i] row, we only need information from dp[i - 1], meaning that we just need to store the previous row, and swap
//them out when we're done. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    int n, k;
    cin >> n >> k;
    int ptr = k;
    int sum = 0;
    while(sum < n){
        sum += ptr;
        ptr ++;
    }
    vector<vector<ll>> dp(2, vector<ll>(n + 1, 0));
    vector<ll> ans(n + 1, 0);
    vector<ll> mRec(k);
    dp[0][0] = 1;
    int row = 0;
    for(int i = k; i <= ptr; i++){
        int moveSize = i;
        for(int j = 0; j <= n; j++){
            int ind = j % moveSize;
            dp[(row + 1) % 2][j] = mRec[ind];
            ans[j] += mRec[ind];
            if(ans[j] >= mod){
                ans[j] -= mod;
            }
            mRec[ind] += dp[row % 2][j];
            if(mRec[ind] >= mod){ 
                mRec[ind] -= mod;
            }
        }
        row ++;
        mRec.push_back(0);
        for(int j = 0; j < mRec.size(); j++){
            mRec[j] = 0;
        }
    }
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
