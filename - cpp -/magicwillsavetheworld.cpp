#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862F

//the idea is to try to first generate all the fire and water magic you need, and then spend it all on killing the monsters. 

//thus, we need to find all possible sums of water magic we will need to generate, and test all of them, taking the minimum time. 

//we can find all of these sums using 01 knapsack dp. The constraints are small enough that we don't have to use bitset. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int w, f;
        cin >> w >> f;
        int n;
        cin >> n;
        int sum = 0;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        for(int i = 0; i < n; i++){
            for(int j = sum; j >= 0; j--){
                if(dp[j]) {
                    dp[j + a[i]] = true;
                }
            }
        }
        int ans = sum;
        for(int i = 0; i <= sum; i++){
            if(!dp[i]) {
                continue;
            }
            int wsum = i;
            int fsum = sum - i;
            //cout << "SUMS : " << wsum << " " << fsum << "\n";
            ans = min(ans, max((wsum / w + (wsum % w == 0? 0 : 1)), (fsum / f + (fsum % f == 0? 0 : 1))));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
