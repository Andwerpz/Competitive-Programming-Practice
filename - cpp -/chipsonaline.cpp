#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1997F

//first, notice that all operations are completely reversible, that is if you transform the chips from state A to state
//B, then you can always get from B -> A. 

//With this in mind, we can reduce any initial configuration of chips to a common form: apply operations
//until all chips are at position 1. Note that a chip initially at position i will contribute fib[i] chips to 
//position 1, where fib[i] is the ith fibonacci number. Denote the number of chips at position 1 after applying
//this compression to a configuration as the 'hash' of that configuration. 

//This observation also gives us a nice way to compute the score of some configuration of chips. We just need
//to find the minimum amount of fibonacci numbers required to sum up to the hash. Since we can only place 1000 chips
//up to position 10, we can precompute the score of all hashes up to fib[10] * 1000 = 55 * 1000. Let dp1[i] = 
//score of hash i. 

//next, for each hash, we need to figure out how many ways to make it using the initial configuration. For a given hash
//h, we want to find the number of ways to choose a multiset of n of the first x fibonacci numbers to sum up to h. 
//This can be solved using dp in fib[x] * n^2 * x time, which is around 550 * 1e6, barely fast enough to pass. 
//dp2[i][j][k] = number of ways where
//i = number of elements in the multiset
//j = which fibonacci number we're on
//k = sum of multiset. 

//finally, we just need to go through all possible hashes h, and see if dp1[h] == m. If this is true, then we add on 
//dp2[n][x][h] to the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vi fib(30);
    fib[0] = 1;
    fib[1] = 1;
    for(int i = 2; i < fib.size(); i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    int maxs = 55 * 1000 + 100;
    //for each sum, what's the minimum amount of fibonacci numbers to represent 
    vi dp1(maxs, 1e9);
    dp1[0] = 0;
    for(int i = 0; i < fib.size(); i++){
        for(int j = 0; j + fib[i] < dp1.size(); j++){
            dp1[j + fib[i]] = min(dp1[j + fib[i]], dp1[j] + 1);
        }
    }
    int n, x, m;
    cin >> n >> x >> m;
    int mod = 998244353;
    //for each sum, compute the number of ways to make it using n of the first x fibonacci numbers. 
    //dp[i][j][k] = number of ways where
    //i = number of values we've used so far
    //j = which of the first x fib numbers we're on
    //k = current sum
    vector dp2(2, vvi(x + 1, vi(maxs, 0)));
    dp2[0][0][0] = 1;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= x; j++){
            for(int k = 0; k < maxs; k++) {
                dp2[1][j][k] = 0;
            }
        }
        for(int j = 0; j <= x; j++){
            for(int k = 0; k < maxs; k++){
                //add current
                if(j != x && k + fib[j] < maxs) {
                    dp2[1][j][k + fib[j]] += dp2[0][j][k];
                    if(dp2[1][j][k + fib[j]] >= mod){
                        dp2[1][j][k + fib[j]] -= mod;
                    }
                }
                //move to next
                if(j != x){
                    dp2[0][j + 1][k] += dp2[0][j][k];
                    if(dp2[0][j + 1][k] >= mod) {
                        dp2[0][j + 1][k] -= mod;
                    }
                }
            }
        }
        swap(dp2[0], dp2[1]);
    }
    int ans = 0;
    for(int i = 0; i < maxs; i++){
        if(dp1[i] == m) {
            ans += dp2[1][x][i];
            if(ans >= mod){
                ans -= mod;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}