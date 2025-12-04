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

//ICPC NAC 2021 - D

//looks like a bait problem fishing for brute force submissions. 
//can just solve using 4D dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    //dp[i][j][k][l] = number of ways to build set where 
    // - currently on ith problem
    // - last picked problems are j and k, j was picked earlier than k
    // - we've picked l problems so far
    int n, _k;
    cin >> n >> _k;
    vi d(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());
    vector dp(n + 1, vector(n + 1, vector(n + 1, vl(_k + 1, 0))));
    dp[0][n][n][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                if(k == n && j != n) continue;
                for(int l = 0; l <= _k; l++){
                    //don't do anything
                    dp[i + 1][j][k][l] += dp[i][j][k][l];
                    //pick problem
                    bool can_pick = false;
                    if(j == n || k == n) can_pick = true;   //haven't picked two problems yet
                    else {
                        int sum = d[j] + d[k];
                        can_pick = sum >= d[i];
                    }
                    if(can_pick && l != _k) dp[i + 1][k][i][l + 1] += dp[i][j][k][l];
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            ans += dp[n][i][j][_k];
        }
    }
    cout << ans << "\n";
    
    return 0;
}