#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1680E

//strange dp problem, you just have to experiment with the transition states, going from left to right. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<string> c(2);
        cin >> c[0] >> c[1];
        int first = 0;
        for(int i = 0; i < c[0].size(); i++){
            if(c[0][i] == '*' || c[1][i] == '*'){
                first = i;
                break;
            }
        }
        vector<vector<int>> dp(2, vector<int>(n, 0));\
        if(c[0][first] == '*' && c[1][first] == '*'){
            dp[0][first] = 1;
            dp[1][first] = 1;
        }
        else{
            dp[0][first] = c[0][first] == '*'? 0 : 1;
            dp[1][first] = c[1][first] == '*'? 0 : 1;
        }
        int ans = min(dp[0][first], dp[1][first]);
        for(int i = first + 1; i < c[0].size(); i++){
            if(c[0][i] == '.' && c[1][i] == '.'){
                dp[0][i] = min(dp[0][i - 1] + 1, dp[1][i - 1] + 2);
                dp[1][i] = min(dp[1][i - 1] + 1, dp[0][i - 1] + 2);
            }
            else if(c[0][i] == '*' && c[1][i] == '*'){
                dp[0][i] = min(dp[1][i - 1] + 2, dp[0][i - 1] + 2);
                dp[1][i] = min(dp[1][i - 1] + 2, dp[0][i - 1] + 2);
            }
            else if(c[0][i] == '*' && c[1][i] == '.'){
                dp[0][i] = min(dp[0][i - 1] + 1, dp[1][i - 1] + 2);
                dp[1][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 2);
            }
            else if(c[0][i] == '.' && c[1][i] == '*'){
                dp[0][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 2);
                dp[1][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 1);
            }
            if(!(c[0][i] == '.' && c[1][i] == '.')){
                ans = min(dp[0][i], dp[1][i]);
            }
            //cout << dp[1][i] << " " << dp[0][i] << endl;
        }
        cout << ans << endl;
    }
    
    return 0;
}
