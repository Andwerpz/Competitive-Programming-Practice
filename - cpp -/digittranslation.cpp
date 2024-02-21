#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - B

//finding the minimum length is pretty easy, it's just 1D dp.

//to find the number of ways to make the minimum string, we can just keep a seperate dp array that piggybacks
//off of the one to find the minimum length. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 9302023;
    string s;
    cin >> s;
    int n = s.size();
    vector<int> dp(n + 1, 1e9);
    vector<ll> dp2(n + 1, 0);
    dp2[0] = 1;
    vector<string> dict = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    dp[0] = 0;
    for(int i = 0; i < n; i++){
        //don't do anything
        if(dp[i] + 1 < dp[i + 1]){
            dp2[i + 1] = 0;
            dp[i + 1] = dp[i] + 1;
        }
        if(dp[i] + 1 == dp[i + 1]){
            dp2[i + 1] = (dp2[i + 1] + dp2[i]) % mod;
        }
        //replace with number
        for(int j = 0; j < dict.size(); j++){
            if(i + dict[j].size() > n){
                continue;
            }
            if(s.substr(i, dict[j].size()) == dict[j]) {
                if(dp[i] + 1 < dp[i + dict[j].size()]) {
                    dp2[i + dict[j].size()] = 0;
                    dp[i + dict[j].size()] = dp[i] + 1;
                }
                if(dp[i] + 1 == dp[i + dict[j].size()]) {
                    dp2[i + dict[j].size()] = (dp2[i + dict[j].size()] + dp2[i]) % mod;
                }
            }
        }
    }
    cout << dp[n] << "\n";
    cout << dp2[n] << "\n";
    
    return 0;
}
