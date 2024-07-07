#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1989D

//first, we can notice that all the metals are independent. This means that we can individual solve the metals
//and then sum their answers. 

//next, notice that the 'cost' of smithing a sword is a[i] - b[i], or how much metal we lose from smithing that sword.
//Of course, we initially need a[i] metal to smith the sword in the first place, but out of all the recipes that
//we can smith, we always want to choose the one with the minimum cost, or min(a[i] - b[i]). 

//so for some starting amount of metal, c, we can easily compute the maximum amount of score we can get. To make 
//choosing the best sword to smith easier, we can arrange them monotonically, with ascending cost associated with 
//descending initial cost. Also note that if we can smith a sword, we can always melt it, so the final score
//should just be 2x the number of swords we can smith

//now the problem is that we have to compute this score for all c[i], and currently our solution is O(nm). Note that 
//if c[i] were <= 10^6, then we could pretty easily solve this issue by creating a lookup table that would tell us 
//for a given c, the maximum score. Also notice that since a[i] <= 10^6, we can always force any c above 10^6 to
//take from the minimum cost sword until it is <= 10^6, which at that point we can just refer to the lookup table
//we created. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    vector<int> c(m);
    for(int i = 0; i < m; i++){
        cin >> c[i];
    }
    vector<pair<int, int>> o(n);
    for(int i = 0; i < n; i++){
        o[i].first = a[i] - b[i];
        o[i].second = a[i];
    }
    sort(o.begin(), o.end());
    {
        vector<pair<int, int>> tmp(0);
        int bind = 0;
        tmp.push_back(o[0]);
        for(int i = 1; i < o.size(); i++){
            if(o[i].first == o[bind].first) {
                continue;
            }
            if(o[i].second >= o[bind].second) {
                continue;
            }
            tmp.push_back(o[i]);
            bind = i;
        }
        o = tmp;
    }
    vector<int> dp(1e6 + 1, 0);
    int ptr = o.size();
    for(int i = 0; i < dp.size(); i++){
        while(ptr != 0 && i >= o[ptr - 1].second) {
            ptr --;
        }
        if(ptr == o.size()) {
            continue;
        }
        dp[i] = dp[i - o[ptr].first] + 1;
    }
    ll ans = 0;
    for(int i = 0; i < m; i++){
        ll cur = c[i];
        if(cur > 1e6) {
            ll diff = cur - 1e6;
            ll intv = o[0].first;
            ll mult = (diff + intv - 1) / intv;
            cur -= intv * mult;
            ans += mult;
        }
        ans += dp[cur];
    }
    ans *= 2;
    cout << ans << "\n";
    
    return 0;
}