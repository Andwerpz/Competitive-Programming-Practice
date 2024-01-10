#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023-2024 ICPC Asia Jakarta Regional J

//we can use dp to simulate the queue. 

//dp[i][j][k] = nr ways to make graph given
//i : nr elements in graph so far
//j : nr elements in 'queue'
//k : true if front of queue doesn't have children yet (0, 1) 

//for base cases, 
//if i == n, then answer is 1
//if i != n && j == 0, then answer is 0

//transitions:
//enqueue element at i into queue; dp[i][j][k] * 2^(j - 1) -> dp[i + 1][j + 1][false]
// - if k == true, we can always do this, otherwise it is required that a[i] > a[i - 1]. 
// - we multiply by 2^(j - 1) because the incoming node can have an edge leading to any element in the queue. 
//pop front element of queue; dp[i][j][k] -> dp[i][j - 1][true]
// - we can do this if j >= 1. 

//note that the time limit is rather tight, you can write an iterative dp, use a primitive array rather than
//vector, and precompute the powers of 2 to get it to not TLE. 

ll mod = 998244353;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    ll ans = 1;
    ll p = a;
    while(b != 0){
        if(b % 2 == 1){
            ans = mul(ans, p);
        }
        p = mul(p, p);
        b /= 2;
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

//dp[i][j][k] = nr ways to make given
//i : nr elements in graph so far
//j : nr elements in 'queue'
//k : true if front of queue doesn't have children yet (0, 1) 
ll dp[5001][5001][2];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    //precompute powers of 2
    vector<ll> pow2(n + 1, 1);
    for(int i = 1; i <= n; i++){
        pow2[i] = (pow2[i - 1] * 2) % mod;
    }
    //base cases
    for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < n + 1; j++){
            dp[i][j][false] = i == n;
            dp[i][j][true] = i == n;
        }
    }
    //solve
    for(int i = n - 1; i > 0; i--){
        for(int j = 1; j <= n; j++){
            //k = false
            {
                //pop queue
                dp[i][j][false] = add(dp[i][j][false], dp[i][j - 1][true]);
                //enqueue child
                if(a[i - 1] < a[i]) {
                    dp[i][j][false] = add(dp[i][j][false], mul(pow2[j - 1], dp[i + 1][j + 1][false]));
                }
            }
            //k = true
            {
                //pop queue
                dp[i][j][true] = add(dp[i][j][true], dp[i][j - 1][true]);
                //enqueue child
                {
                    dp[i][j][true] = add(dp[i][j][true], mul(pow2[j - 1], dp[i + 1][j + 1][false]));
                }
            }
        }
    }
    cout << dp[1][1][true] << "\n";
    
    return 0;
}
