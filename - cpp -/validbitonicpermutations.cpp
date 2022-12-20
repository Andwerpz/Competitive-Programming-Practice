#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1763D

//very proud of this one :))

//lets first figure out how many bitonic permutations of length n there are. To count the number of bitonic permutations, 
//we can simply just count the number of monotonic permutations of length < n ending on value n. Then, in order to make 
//such a permutation into a bitonic one, we simply just add the missing numbers to the end of the permutation in descending order. 

//To compute the amount of permutations, we can use a 2 state dp, where dp[i][j] is the number of ways to make a monotonic permutation
//of length i, ending on value j. The answer to the total number of bitonic permutations is just the sum of dp[i][n], where 1 < i < n. 

//now we have to add in the two constraints, where two indices of the permutation, x_ind, y_ind, have to be certain values, x, y. 
//forcing any dp[x_ind][j] = 0 where j != x and dp[i][x] = 0 where i == x_ind, likewise for y, is easy enough, but the problem is 
//that this doesn't always create valid bitonic permutations. The problem lies in the fact that we can only guarantee that the 
//ascending portion is valid, but with the extra restrictions, the descending portion is not guaranteed to be valid. 

//the exact problem is that when we construct the ascending sequence ending on n, we don't care about how many 'skipped' 
//numbers there are, and is that enough to place x at x_ind, and y at y_ind, without breaking the ascending or descending order. 
//to fix that, we can use another two dp states for x and y to keep track of how many numbers in the permutation are above x and y. 

//although the solution above is correct, it takes way too much time; we need to go from 4 states to 3. The first optimization that 
//can be made is to always fix the ordering of x and y. Notice that when x_ind < y_ind, and x < y, the peak of any valid bitonic permutation must
//occur after x, meaning that x is always in the ascending portion of any valid permutation. If this is the case, then we can eliminate the state
//that describes how many values are above x, since we don't need to check that anymore. 

//To guarantee that x < y, we can flip the permutation. This doesn't change the answer since we are counting bitonic permutations, and
//the count should be the same forwards as well as backwards. 

//so finally, dp[i][j][k] = number of ways to create a monotonically increasing sequence of length i, ending on value j, with k values in
//the sequence being greater than y. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, xind, yind, x, y;
        cin >> n >> xind >> yind >> x >> y;
        xind--;
        yind--;
        x--;
        y--;

        //dp[i][j][k] :
        //how many ways is there to make a monotonically increasing permutation of length i, ending on 
        //value j, with k elements greater than y?
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));

        //we want x to come first, and be less than y
        if(x > y) { //this makes sure that x is less than y
            //'flip' the permutation
            xind = n - xind - 1;
            yind = n - yind - 1;
        }
        if(xind > yind) {   //this makes sure that x comes before y. 
            //swap x and y
            int temp = xind;
            xind = yind;
            yind = temp;

            temp = x;
            x = y;
            y = temp;
        }
        //cout << n << " " << x << " " << y << endl;
        int mod = (int) (1e9 + 7);
        int ans = 0;
        if(xind == 0){
            dp[0][x][0] = 1;
        }
        else {
            for(int i = 0; i < n; i++){
                dp[0][i][(i > y? 1 : 0)] = 1;
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    // - Always adding +1 i forwards. 
                    // - if cur j > y, then look at dp[i - 1][0 to (j - 1)][k - 1].
                    // - else look at dp[i - 1][0 to (j - 1)][k], it doesn't make sense for k != 0 when j <= y. 

                    if(j != 0 && i != 0){
                        if(j > y) {
                            dp[i][j][k] += k == 0? 0 : dp[i - 1][j - 1][k - 1];
                        }
                        else {
                            dp[i][j][k] += dp[i - 1][j - 1][k];
                        }
                        if(dp[i][j][k] >= mod) {
                            dp[i][j][k] -= mod;
                        }
                    }
                    if((i == xind && j != x) || (i == yind && j != y)){
                        dp[i][j][k] = 0;
                    }
                    if((i != xind && j == x) || (i != yind && j == y)){
                        dp[i][j][k] = 0;
                    }

                    //use pfx sums to replace this extra n factor

                    // if(i != n - 1 && k != n - 1) {
                    //     for(int l = j + 1; l < n; l++){
                    //         if((i + 1 == xind && l != x) || (l == x && i + 1 != xind)){
                    //             continue;
                    //         }
                    //         if((i + 1 == yind && l != y) || (l == y && i + 1 != yind)) {
                    //             continue;
                    //         }
                    //         dp[i + 1][l][k + (l > y? 1 : 0)] += dp[i][j][k];
                    //         dp[i + 1][l][k + (l > y? 1 : 0)] %= mod;
                    //     } 
                    // }

                    //cout << dp[i][j][k] << " ";
                    
                    bool isValid = true;
                    if(j != n - 1) {
                        isValid = false;
                    }
                    if(i == n - 1){
                        isValid = false;
                    }
                    if(i <= xind){
                        isValid = false;
                    }
                    if(i < yind && yind - i - 1 != (n - 1) - y - k) {
                        isValid = false;
                    }
                    if(isValid){
                        ans += dp[i][j][k];
                        if(dp[i][j][k] != 0){
                            //cout << i << " " << j << " " << k << endl;
                        }
                        if(ans >= mod){
                            ans -= mod;
                        }
                    }
                }
                //cout << endl;
            }
            //cout << endl;

            //building pfx sum for the next i. 
            for(int k = 0; k < n; k++){
                for(int j = 1; j < n; j++){
                    dp[i][j][k] += dp[i][j - 1][k];
                    if(dp[i][j][k] >= mod){
                        dp[i][j][k] -= mod;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
