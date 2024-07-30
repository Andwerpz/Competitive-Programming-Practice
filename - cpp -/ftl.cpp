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

//Codeforces - 1743E

//we can solve this using brute force dp, and I claim that we'll only generate around h^2 states. 
//first, swap around the lasers such that t1 <= t2, or the second laser has the greater reload time. 

//dp[i][j] = minimum time required s.t.
//i = health remaining, j = reload time on second laser. I maintain that the reload time on the first laser 
//is always t1. 

//transitions are as follows: 
//shoot laser p1
//wait until p1 and p2 are charged, and shoot them both. Only do this if j < t1 * 2. 

//I claim that if we make j sparse, we'll only generate around h^2 states. Since each shot of any laser is guaranteed
//to take at least 1 point of health off, and the only point where we branch into multiple states is j < t1 * 2, 
//each dp[i] can have at most i unique j's, or h^2 states in total. 

void dpins(vector<map<ll, ll>>& m, int h, ll r, ll t) {
    if(!m[h].count(r)) {
        m[h][r] = 1e18;
    }
    m[h][r] = min(m[h][r], t);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll p1, t1, p2, t2, h, s;
    cin >> p1 >> t1 >> p2 >> t2 >> h >> s;
    //force t1 <= t2
    if(t1 > t2) {
        swap(p1, p2);
        swap(t1, t2);
    }
    vector<map<ll, ll>> dp(h + 1);
    ll ans = 1e18;
    dp[h][t2] = 0;
    for(int i = h; i > 0; i--){
        for(auto j = dp[i].begin(); j != dp[i].end(); j++){
            ll t = j->second;
            ll r = j->first;
            if(r < t1 && h + s - p2 <= 0) {
                ans = min(ans, t + r);
            }
            //shoot p1
            {
                ll nr = r, nh = i, nt = t + t1;
                if(r <= t1) {
                    if(r < t1){
                        nh = (nh + s - p2) + s - p1;
                    }
                    else {
                        nh = nh + s - p1 - p2;
                    }
                    nr = nr + t2 - t1;
                }
                else {
                    nr -= t1;
                    nh = nh + s - p1;
                }
                nh = max(0ll, nh);
                dpins(dp, nh, nr, nt);
            }
            //wait and shoot both
            if(r < 2 * t1){
                ll nr = t2, nh = i + s - p1 - p2, nt = t + max(r, t1);
                nh = max(0ll, nh);
                dpins(dp, nh, nr, nt);
            }
        }
    }
    for(auto i = dp[0].begin(); i != dp[0].end(); i++){
        ans = min(ans, i->second);
    }
    cout << ans << "\n";
    
    return 0;
}