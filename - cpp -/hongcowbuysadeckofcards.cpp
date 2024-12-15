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

//Codeforces - 745E

//bitmask dp. naively, we want to keep track of which cards we've bought, and how many tokens of each type were required to
//buy them. However, the amount of tokens can be rather large. This is why we only keep track of the number of tokens we save
//as we can then derive the required tokens by subtracting that from the sum. 

//we need to do one more optimization: for every amount of red tokens saved, we only care about the maximum amount of blue 
//tokens saved. This saves us an extra factor of 120ish. 

//so dp[i][j] = maximum amount of blue tokens saved given we've bought all cards in bitmask i, and saved j red tokens. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi c(n), r(n), b(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s >> r[i] >> b[i];
        c[i] = s[0] == 'R';
    }
    //dp[i][j] = max number of B saved given bitmask i of bought cards, and j R saved
    vvi dp((1 << n), vi(130, -1));
    dp[0][0] = 0;
    for(int i = 0; i < (1 << n); i++){
        int rcnt = 0, bcnt = 0;
        for(int j = 0; j < n; j++){
            if(i & (1 << j)) {
                rcnt += c[j] == 1;
                bcnt += c[j] == 0;
            }
        }
        for(int j = 0; j < dp[i].size(); j++){
            if(dp[i][j] == -1) continue;
            for(int k = 0; k < n; k++){
                if(i & (1 << k)) continue;
                int nr = j + min(r[k], rcnt);
                int nb = dp[i][j] + min(b[k], bcnt);
                dp[i ^ (1 << k)][nr] = max(dp[i ^ (1 << k)][nr], nb);
            }
        }
    }
    ll ans = 0;
    ll rsum = 0, bsum = 0;
    for(int i = 0; i < n; i++){
        rsum += r[i];
        bsum += b[i];
    }
    ans = max(rsum, bsum);
    for(int i = 0; i < dp[(1 << n) - 1].size(); i++){
        if(dp[(1 << n) - 1][i] == -1) continue;
        ans = min(ans, max(rsum - i, bsum - dp[(1 << n) - 1][i]));
    }
    ans += n;
    cout << ans << "\n";
    
    return 0;
}