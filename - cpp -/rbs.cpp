#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1598F

//actually pretty straightforwards brute force dp problem. 

//we'll do dp across all bitsets of included strings, so dp[i] = max number of RBS prefixes where we have
//included the strings represented by bitset i. Transitions are going to be including another string. 

//How do we quickly compute the number of new prefixes we'll generate? Well, first observation is that any
//new RBS prefix must be formed within the new string we're appending. Second, if we treat '(' = 1 and
//')' = 0, then any RBS prefix must have sum = 0, and any prefix within must have sum >= 0. So if we're
//adding a string, and the current prefix has sum p, then we're looking for all occurrences of -p in the 
//string we're adding, and those will be the new RBS prefixes. 

//This also explains why we don't have to store the order, or even the last string we added as another dp
//state, since the only thing that matters when transitioning is the prefix sum, and that doesn't change
//when changing the order of the strings. 

//One caveat, remember that any prefix within an RBS must have sum >= 0. This means that not all occurrences 
//of -p are necessarily going to generate an RBS, between the occurrences, the prefix sum may dip below 0.
//This can be handled pretty easily in the precomputation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    vector<vector<int>> m(n);
    vector<int> mx_neg(n, 0);
    vector<int> sum(n, 0);
    for(int i = 0; i < n; i++){
        m[i] = vector<int>(s[i].size() + 1, 0);
        int mn = 0;
        int pfx = 0;
        for(int j = 0; j < s[i].size(); j++){
            pfx += s[i][j] == '('? 1 : -1;
            mn = min(mn, pfx);
            if(pfx == mn){
                m[i][-pfx] ++;
            }
            mx_neg[i] = min(mx_neg[i], pfx);
        }
        sum[i] = pfx;
    }
    vector<int> dp((1 << n), -1e9);
    dp[0] = 0;
    int ans = 0;
    for(int i = 0; i < (1 << n); i++){
        ans = max(ans, dp[i]);
        int pfx = 0;
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){
                pfx += sum[j];
            }
        }
        for(int j = 0; j < n; j++){
            if(i & (1 << j)) {
                continue;
            }
            if(pfx + mx_neg[j] < 0){
                ans = max(ans, dp[i] + (pfx < 0 || pfx >= m[j].size()? 0 : m[j][pfx]));
                continue;
            }
            int next = i | (1 << j);
            dp[next] = max(dp[next], dp[i] + (pfx < 0 || pfx >= m[j].size()? 0 : m[j][pfx]));
        }
    }
    cout << ans << "\n";
    
    return 0;
}