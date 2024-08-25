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

//Kattis - rangeediting

//identical problem to https://leetcode.com/problems/strange-printer/, except we start with some initial 0s
//and the constraints are tighter. 

//define dp[i][j] as the minimum operations to create segment [i, j). Note that if a[i] == a[j - 1], then if we 
//solve the suffix [i + 1, j), then we can get a[i] for free. Therefore, we can solve each segment in linear time,
//putting the total complexity at O(n^3). 

//to account for the initial 0s the array starts with, we can append and prepend a 0 onto the array and spend
//an extra operation setting everything to 0. Then, at the end, we'll just subtract 1 from the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    a.push_back(0);
    a.insert(a.begin(), 0);
    n += 2;
    vvi dp(n + 1, vi(n + 1, 1e9));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < n; j++){
            int l = j;
            int r = j + i;
            if(r > n) {
                continue;
            }
            if(i == 1){
                dp[l][r] = 1;
                continue;
            }
            int ptr = l;
            while(ptr != r && a[ptr] == a[r - 1]) {
                ptr ++;
            }
            int minans = 1e9;
            for(int k = ptr + 1; k < r; k++){
                minans = min(minans, dp[ptr][k] + dp[k][r]);
            }
            if(ptr == r){
                minans = 1;
            }
            dp[l][r] = minans;
        }
    }
    cout << dp[0][n] - 1 << "\n";
    
    return 0;
}