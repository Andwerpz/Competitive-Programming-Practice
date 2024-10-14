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

//2024 ICPC NAC - G

//denote ev(r, c) as the expected time to get from (r, c) to (n, m). 

//if we stand at some cell r, c, the current timer will be uniformly distributed in range [0, p], and
//the arrow will be uniformly to the right or down.

//next, say that ev_right = ev(r, c + 1), and ev_down = ev(r + 1, c), and ev_right < ev_down. If the arrow is
//initially pointing to the right, then we just travel right. However, if the arrow is pointed down, then we
//might want to wait for the arrow to point right. 

//if the time left is less than ev_down - ev_right, then we benefit by waiting, otherwise we should
//just go down. 

ld solve(int r, int c, vvd& dp, ld p) {
    if(r == dp.size() || c == dp[0].size()) {
        return 1e18;
    }
    if(dp[r][c] != -1){
        return dp[r][c];
    }
    ld ans = -1;
    if(r == dp.size() - 1){
        ans = solve(r, c + 1, dp, p) + p / 4.0;
    }   
    else if(c == dp[0].size() - 1){
        ans = solve(r + 1, c, dp, p) + p / 4.0;
    } 
    else {
        ld ev_right = 0, ev_down = 0;
        ev_right = solve(r, c + 1, dp, p);
        ev_down = solve(r + 1, c, dp, p);
        if(ev_right > ev_down){
            swap(ev_right, ev_down);
        }
        ld diff = ev_down - ev_right;
        ld prob = diff / p;
        ev_down = (1.0 - prob) * ev_down + prob * (ev_right + diff / 2.0);
        ans = (ev_right + ev_down) / 2.0;
    }
    dp[r][c] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    ld p;
    cin >> n >> m >> p;
    n --;
    m --;
    vvd dp(n + 1, vd(m + 1, -1));
    dp[n][m] = 0;
    cout << fixed << setprecision(10) << solve(0, 0, dp, p) << "\n";
    
    return 0;
}