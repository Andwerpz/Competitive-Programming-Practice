#include <bits/stdc++.h>
typedef long long ll;
using namespace std; 

//CSCE 430 Spring 2023 - Lab 12 F

//dp[n][b.size()];

//dp[i][j] = number of strings of length i where the suffix of length j is equal to prefix of b of length j. 

//for each dp[i][j], you can either add the b[j] to the end of the string, transitioning to dp[i + 1][j + 1], or 
//you can add the opposite of b[j] to the end. 

//if you add the wrong character, then you need to figure out the maximum j where the suffix of length j is equal to
//the prefix of b of length j. This can be precomputed before the dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 1e9 + 7;
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> b;
        string s;
        cin >> s;
        for(int i = 0; i < s.size(); i++){
            b.push_back(s[i] - '0');
        }
        vector<int> t(b.size(), 0);
        for(int i = 0; i < b.size(); i++){
            vector<int> tmp;
            for(int j = 0; j < i; j++){
                tmp.push_back(b[j]);
            }
            tmp.push_back(b[i] == 0? 1 : 0);
            int maxPre = 0;
            for(int j = tmp.size(); j >= 0; j--){
                bool isValid = true;
                for(int k = 0; k < j; k++){
                    if(tmp[tmp.size() - k - 1] != b[j - k - 1]){
                        isValid = false;
                        break;
                    }
                }
                if(isValid) {
                    maxPre = j;
                    break;
                }
            }
            t[i] = maxPre;
        }
        vector<vector<ll>> dp(n + 1, vector<ll>(b.size() + 1, 0));
        dp[0][0] = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < b.size(); j++){
                //right char
                dp[i + 1][j + 1] += dp[i][j];
                dp[i + 1][j + 1] %= mod;
                //wrong char
                dp[i + 1][t[j]] += dp[i][j];
                dp[i + 1][t[j]] %= mod;
            }
        }
        ll ans = 0;
        for(int i = 0; i < b.size(); i++){
            ans += dp[n][i];
            ans %= mod;
        }
        cout << ans << "\n";
    }

    return 0;
}