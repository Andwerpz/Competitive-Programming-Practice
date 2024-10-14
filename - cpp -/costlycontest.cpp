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

//KTH Challenge 2021 - C

//first, can precompute what difficulties are possible to make given the m problems. 
//then for each person, compute the maximum difficulty sum contest that they can full solve, and that
//we can make using the m problems. 

//from here, just have to partition the array into k segments such that the sum of amounts of maximums is 
//minimized. 

//if c is the count of the maximum in the entire array, then I claim the answer is always max(k, c). 
//if c >= k, then each partition should contain at least one person with maximum difficulty. 
//if c < k, we can just make singleton partitions until c >= k is achieved. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m, k, t;
    cin >> n >> m >> k >> t;
    vl s(n), d(m);
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    for(int i = 0; i < m; i++){
        cin >> d[i];
    }
    sort(d.begin(), d.end());
    vb dp(t + 1, false);    //what difficulties are possible?
    dp[0] = true;
    for(int i = 0; i < m; i++){
        for(int j = t - d[i]; j >= 0; j--){
            dp[j + d[i]] = dp[j + d[i]] || dp[j];
        }
    }
    vl dl(t + 1, 0);
    for(int i = 1; i <= t; i++){
        dl[i] = dp[i]? i : dl[i - 1];
    }
    ll mxcnt = 0;
    ll mx = 0;
    for(int i = 0; i < n; i++){
        ll mxd = dl[t / s[i]];
        if(mxd > mx) {
            mx = mxd;
            mxcnt = 0;
        }
        if(mxd == mx){
            mxcnt ++;
        }
    }
    cout << max(mxcnt, k) << "\n";
    
    return 0;
}