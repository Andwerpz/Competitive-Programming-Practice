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

//RMRC 2021 - G

//actually kinda tricky EV problem. (at least when trying to speedsolve)

//ev[i] = expected number of matches to get a prize given you start at i percent chance to 
//get a prize.

//note that ev[100] = 1 / (1 - l) where l is the probability of losing.

//then, the expected number of matches to get the gorilla thing is ev[0] / g

ld dfs(int i, vd& dp, int dl, int dw, ld l) {
    i = min(i, 100);
    if(i == 100){
        return 1.0 / (1.0 - l);
    }
    if(dp[i] != -1){
        return dp[i];
    }
    ld ans = 0;
    //lose
    ans += l * (dfs(i + dl, dp, dl, dw, l) + 1);
    //win, no prize
    ans += (1.0 - l) * (1.0 - (ld) i / 100.0) * (dfs(i + dw, dp, dl, dw, l) + 1);
    //win, prize
    ans += (1.0 - l) * ((ld) i / 100.0) * 1;
    dp[i] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int dl, dw;
    ld g, l;
    cin >> dl >> dw >> g >> l;
    g /= 100.0;
    l /= 100.0;
    vd dp(101, -1);
    dfs(0, dp, dl, dw, l);
    for(int i = 0; i < 100; i++){
        // cout << fixed << setprecision(10) << dp[i] << "\n";
    }
    cout << fixed << setprecision(10) << (1.0 / g) * dp[0] << "\n";
    
    return 0;
}