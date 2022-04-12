
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1639

//given string a, a[:i] represents all letters of string a from 1 - i. 

//dp[i][j] represents the amount of moves required to tranform s1[:i] to s2[:j]. 

//we have 3 possible operations we can do. Take the min out of them

//1: remove char from s1. dp[i][j] = dp[i - 1][j] + 1
//moves required to go from s1[:i] to s2[:j] = s1[:i - 1] to s2[:j] + 1

//2: remove char from s2. dp[i][j] = dp[i][j - 1] + 1
//moves required to go from s1[:i] to s2[:j] = s1[:i] to s2[:j - 1] + 1

//3: transform s1[i - 1] into s2[j - 1]. dp[i][j] = dp[i - 1][j - 1] + 1;
//moves required to go from s1[:i] to s2[:j] = s1[:i - 1] to s2[:j - 1] + 1
//if(s1[i - 1] == s2[j - 1]), then we don't add one, since they are already equal and no transform is needed.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2;
    cin >> s1 >> s2;
    //cout << s1 << " " << s2 << endl;
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));
    dp[0][0] = 0;
    for(int i = 0; i <= n; i++){
        //cout << s1[i] << ": ";
        for(int j = 0; j <= m; j++){
            if(i != 0){
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1); //remove s1[i - 1];
            }
            if(j != 0){
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1); //remove s2[j - 1];
            }
            if(i != 0 && j != 0){
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1]? 0 : 1));   //change s1[i - 1] to s2[j - 1]
            }
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    cout << dp[n][m] << endl;
    
    return 0;
}
