#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1987 F1, F2

//to be honest, I don't really understand how this solution is motivated, but it does work. 

//let's define dp[l][r] as the amount of moves required to happen before position l such that you can completely
//remove the segment [l, r). We have two possible transitions: 

//merging two segments: We look at segments [l, k) and [k, r). At a minimum, we need to be able to remove 
//segment [l, k), but segment [k, r) will be able to get some help from [l, k), so
//dp[l][r] = max(dp[l][k], dp[k][r] - (r - k) / 2).

//doing an operation after completely removing a segment: if this is confusing, refer to the editorial's
//bracket sequence analogy. If we completely remove segment [l + 1, r - 1), and then we do an operation on 
//position l, then we are effectively removing segment [l, r) in the original array. But this can only be done 
//if the required amount of moves to remove segment [l + 1, r - 1) is less than or equal to the moves required
//to remove a[l]. So, dp[l][r] = (l - a[l]) / 2. Of course, l - a[l] needs to be even and positive. 

//Now, to make the above work useful, we define a new dp, lets say pdp[i] = maximum amount of operations we
//can perform on the prefix [0, i). Of course, pdp[i] is at least equal to pdp[i - 1]. But we can also try to 
//remove the first j elements from [0, i), and we can only do that if dp[i - j][i] <= pdp[i - j]. 

//final complexity is O(n^3). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] = i + 1 - a[i];
        }
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
        //base cases
        for(int i = 0; i < n; i++){
            dp[i][i] = 0;
        }
        for(int i = 2; i <= n; i += 2) {
            for(int j = 0; j <= n - i; j++) {
                int l = j;
                int r = l + i;
                //can merge two segments
                for(int k = l + 2; k <= r; k++){
                    dp[l][r] = min(dp[l][r], max(dp[l][k], dp[k][r] - (k - l) / 2));
                }
                //can do operation on a[l] and a[r - 1]
                if(a[l] / 2 >= dp[l + 1][r - 1] && a[l] % 2 == 0){
                    dp[l][r] = min(dp[l][r], max(a[l] / 2, dp[l + 1][r - 1]));
                }
            }
        }
        //maximum amount of operations performable on prefix
        vector<int> pdp(n + 1, 0);
        for(int i = 1; i <= n; i++){
            //inherit previous prefix
            pdp[i] = pdp[i - 1];
            //remove some segment from current prefix
            for(int j = i - 2; j >= 0; j -= 2){
                int l = j;
                int r = i;
                if(pdp[l] >= dp[l][r]) {
                    pdp[i] = max(pdp[i], pdp[l] + (r - l) / 2);
                }
            }
        }
        cout << pdp[n] << "\n";
    }
    
    return 0;
}