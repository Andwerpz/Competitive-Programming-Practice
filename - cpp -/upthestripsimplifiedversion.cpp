
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1561D1

//this one was actually easier than i thought. The 6 second time limit really does help in letting O(n * sqrt(n)) solutions pass

//this problem is obviously dp. For subtracting positions, that is easily represented by adding at dp[i], all the moves from dp[1] to dp[i - 1]. 

//division is slightly harder. Notice that if the current position is x, then there are only sqrt(x) positions that you can go to. So you can start from 
//You can see that the divisors that result from 1 - 2 is x / 1 - x / 2. Just repeat the process until the divisors become 1.

//read tutorial for better explanation.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, mod;
    cin >> n >> mod;
    vector<ll> dp(n + 1);
    vector<ll> pfx(n + 1);
    dp[1] = 1;
    ll sum = 1;
    for(int i = 2; i < dp.size(); i++){
        dp[i] = sum;

        dp[i] += dp[1];
        int pointer = i - 1;
        while(true){
            if(pointer <= 1){
                break;
            }
            int startMult = i / pointer;
            int end = i / (startMult + 1) + 1;
            ll range = pointer - end + 1;
            dp[i] += (dp[startMult] * range) % mod;
            dp[i] %= mod;
            //cout << pointer << " " << end << " ";
            pointer = end - 1;
        }
        
        
        //cout << endl;
        sum += dp[i];
        sum %= mod;
        //cout << "DP: " << dp[i] << " SUM: " << sum << endl;
    }
    cout << dp[n] << endl;

    return 0;
}



