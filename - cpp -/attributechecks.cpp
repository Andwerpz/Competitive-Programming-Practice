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

//Codeforces - 2025D

//tricky dp problem. Naive method is to have 2D dp where dp[i][j] = max checks passed and
//i = number of points into Int, and j = number of points into Str.

//first idea is that if we process the events in order, then keeping both number of points into
//Int and Str is redundant, we can derive one from the other given the total amount of points so
//far. So dp[i] = max checks given i = number of Int, and we'll keep track of the total amount
//of points so far. 

//second idea is to speed up transitions. Currently, if we want to apply a check, we'll have to do a
//range update. We can speed this up by using an array to store all range updates, and then when we
//see the next point, we'll apply them all at once, prefix sum style. 

//this should run in O(n + m^2)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    m ++;
    vi r(n);
    for(int i = 0; i < n; i++){
        cin >> r[i];
    }
    r.push_back(0);
    n ++;
    int cnt = 0;
    vi dp(m + 1, -1);   //dp[i] = max checks passed where you've spent i points on int so far. 
    dp[0] = 0;
    vi dpinc(m + 2, 0);
    for(int i = 0; i < n; i++){
        if(r[i] == 0){
            // cout << "APPLY DPINC : " << i << "\n";
            //apply dpinc
            for(int j = 1; j <= m; j++){
                dpinc[j] += dpinc[j - 1];
            }
            for(int j = 0; j <= m; j++){
                if(dp[j] != -1){
                    dp[j] += dpinc[j];
                }
            }
            dpinc = vi(m + 2, 0);
            //transition state
            vi ndp(m + 1, -1);
            for(int j = 0; j <= m; j++){
                if(dp[j] != -1) {
                    ndp[j] = max(ndp[j], dp[j]);    //str
                    ndp[j + 1] = max(ndp[j + 1], dp[j]);    //int
                }
            }
            dp = ndp;
            cnt ++;
        }
        else if(r[i] > 0){
            //int check
            dpinc[r[i]] ++;
        }
        else {
            //r[i] < 0, str check
            r[i] = abs(r[i]);
            dpinc[0] ++;
            dpinc[max(0, cnt - r[i] + 1)] --;
        }
    }
    int ans = 0;
    for(int i = 0; i <= m; i++){
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
    
    return 0;
}