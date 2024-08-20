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

//Codeforces - 2002 F1

//this only solves the easy version. 

//this problem is a 'analyze to see how much brute forcing you can get away with' type problem. 
//for small n (< 50), we can just brute force dfs with memoization to find the best answer. 

//with n >= 50, there is a better approach. Since n = m, we can first assume that l > f. 
//Then, we raise a to the largest prime under n, and b to the largest prime under a. From there, we do
//our brute force dfs. 

vector<int> lp; //lowest prime factor 
vector<int> pr; //prime list

void prime_sieve(int n) {
    lp = vector<int>(n + 1);
    pr = vector<int>(0);
    for(int i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

int find_pr(int val) {
    if(val < 2){
        return 1;
    }
    int low = 0;
    int high = pr.size() - 1;
    int ans = 2;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(pr[mid] <= val) {
            ans = max(ans, pr[mid]);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return ans;
}

ll calc_ans(ll a, ll b, ll l, ll f, ll n, map<pll, ll>& dp){
    if(a > n || b > n || gcd(a, b) > 1){
        return 0;
    }
    if(dp.count({a, b})) {
        return dp[{a, b}];
    }
    // cout << "CALC ANS : " << a << " " << b << "\n";
    ll ans = l * a + f * b;
    ans = max(ans, calc_ans(a + 1, b, l, f, n, dp));
    ans = max(ans, calc_ans(a, b + 1, l, f, n, dp));
    dp.insert({{a, b}, ans});
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    prime_sieve(2e7 + 100);
    int t;
    cin >> t;
    while(t--){
        ll n, m, l, f;
        cin >> n >> m >> l >> f;
        if(l < f) {
            swap(l, f);
        }
        ll a = find_pr(n);
        ll b = find_pr(a - 1);
        if(n < 50) {
            a = 1;
            b = 1;
        }
        map<pll, ll> dp;
        cout << calc_ans(a, b, l, f, n, dp) << "\n";
    }
    
    return 0;
}