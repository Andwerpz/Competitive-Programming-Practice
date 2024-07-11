#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1982C

//a naive dp solution would be like this:
//dp[i] = maximum score after taking the first i cards
//with transitions dp[i] -> dp[j] + (1 if range sum is within [l, r])

//the problem with the above solution is for every state, there is n - i transitions, so the total complexity
//is O(n^2). 

//we can actually get rid of most of those transitions with the following observation: taking some amount of
//cards off of the deck is equivalent to taking 1 card off the deck multiple times, except in the case where your
//score increases. Thus, the only 2 transitions we need to think about are taking 1 card, and taking
//just enough cards such that the score increases. 

//we can keep track of the minimum amount of cards required for a score increase using a 2 pointer technique. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, l, r;
        cin >> n >> l >> r;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> dp(n + 1, 0);
        int ptr = 0;
        int sum = 0;
        for(int i = 0; i < n; i++){
            while(ptr != n && sum < l) {
                sum += a[ptr];
                ptr ++;
            }
            if(sum >= l && sum <= r) {
                dp[ptr] = max(dp[ptr], dp[i] + 1);
            }
            dp[i + 1] = max(dp[i + 1], dp[i]);
            sum -= a[i];
        }
        cout << dp[n] << "\n";
    }
    
    return 0;
}