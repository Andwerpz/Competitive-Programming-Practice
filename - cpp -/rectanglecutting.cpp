
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1744

//dp[i][j] represents the amount of cuts required to turn a rectangle of width i and height j into squares. 

//we know that dp[i][i] = 0 for all i, since if a rectangle has the same width and height, then it is a square. 

//for dp[i][j], there are (i - 1) vertical cuts we can do and (j - 1) horizontal cuts we can do. 
//we can try all of them, and take the minimum out of them. 

//for each cut, we need to sample the dp array at 2 points, one for each new rectangle, and add 1, since we 
//did a cut. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    cin >> a >> b;
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 1e9));
    for(int i = 1; i <= min(a, b); i++){
        dp[i][i] = 0;   //these are squares
    }
    for(int i = 1; i <= a; i++){
        for(int j = 1; j <= b; j++){
            for(int w = 1; w <= i - 1; w++){
                dp[i][j] = min(dp[i][j], dp[w][j] + dp[i - w][j] + 1);  //cutting vertically
            }
            for(int h = 1; h <= j - 1; h++){
                dp[i][j] = min(dp[i][j], dp[i][h] + dp[i][j - h] + 1);  //cutting horizontally
            }
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    cout << dp[a][b] << endl;
    
    return 0;
}
