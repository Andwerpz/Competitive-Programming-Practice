#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 730J

//let's say that we already know the minimum number of bottles, 'mink'. 
//we can choose mink bottles to dump all the soda into. 

//dp[i][j][k] = minimum amount of soda in 'unchosen' bottles where
//i = we've considered the first i bottles
//j = we've chosen j of the i bottles
//k = amount of vacant capacity in the chosen bottles - amount of soda in the unchosen bottles. 

//note that we should allow k to go negative. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);   //soda in bottle
    vector<int> b(n);   //capacity of bottle
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    int unv = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(100 * 100 * 2 + 1, unv));
    vector<vector<int>> ndp(n + 1, vector<int>(100 * 100 * 2 + 1, unv));
    int kzero = 100 * 100;
    dp[0][kzero] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fill(ndp[j].begin(), ndp[j].end(), unv);
        }
        for(int j = 0; j < n; j++){
            for(int k = 0; k < dp[0].size(); k++){
                if(dp[j][k] == unv) {
                    continue;
                }
                //take current bottle
                {
                    int nk = k + b[i] - a[i];
                    ndp[j + 1][nk] = min(ndp[j + 1][nk], dp[j][k]);
                }
                //don't take current bottle
                {
                    int nk = k - a[i];
                    ndp[j][nk] = min(ndp[j][nk], dp[j][k] + a[i]);
                }
            }
        }
        swap(dp, ndp);
    }
    int mink = 1e9;
    int mint = 1e9;
    for(int i = 0; i <= n; i++){
        for(int j = kzero; j < dp[0].size(); j++){
            if(dp[i][j] == unv) {
                continue;
            }
            if(i <= mink) {
                if(i < mink){
                    mint = dp[i][j];
                }
                else {
                    mint = min(mint, dp[i][j]);
                }
                mink = i;
            }
        }
    }
    cout << mink << " " << mint << "\n";
    
    return 0;
}
