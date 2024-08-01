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

//Codeforces - 1930 D1, D2

//given some pattern p, how do we generate a minimal p-good binary string s? first notice that any 1 bit in
//s can 'suppport' 3 1 bits in p, the one with the same index, and the two to the immediate left and right. 
//Actually, if we just greedily generate s like this, it's actually minimal. 

//example:
//p : 11110110000000111111
//s : 01001001000000010010

//effectively every 1 bit in s projects a size 3 segment around itself that can support 1 bits in p.
//so for the easy version, it's sufficient to just loop through all substrings and compute their answers. 

//for the hard version however, we need a faster solution. Consider an easier problem where we're only 
//interested in the sum of f(s) for all suffixes of s. We can use dp to solve this problem, dp[i] = 
//number of size 3 segments that start at i across all suffixes. For every i, we increment 
//dp[nxt[i]] by 1, and also add to dp[nxt[i + 3]] += dp[i]. nxt[i] just stores the index of the next
//1 bit after i. 

//the number of size 3 segments across all suffixes is just the sum of dp[i] for i in range [0, n). 

//to solve the original problem, notice that we then just need to incrementally cut off the last bit of
//s. This is equivalent to subtracting dp[n - 1], and then dp[n - 2], and taking the remaining sum every time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vl dp(n + 1, 0);    //how many 3-segments start at each index
        vi nxt(n + 4, n);  //index of next 1
        for(int i = n - 1; i >= 0; i--){
            if(s[i] == '1'){
                nxt[i] = i;
            }
            else {
                nxt[i] = nxt[i + 1];
            }
        }
        for(int i = 0; i < n; i++){
            dp[nxt[i]] ++;
            dp[nxt[i + 3]] += dp[i];
        }
        ll ans = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++){
            sum += dp[i];
        }
        for(int i = n - 1; i >= 0; i--){
            ans += sum;
            sum -= dp[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}