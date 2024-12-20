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

//AtCoder - ARC159D

//Let's look at how normal LIS works, and perhaps we can use it to solve this problem. With normal LIS, we define
//dp[i] as the minimum ending value of an increasing subsequence of length i. To update the dp, we consider each 
//element in the array from left to right, and then binary search for the first i where dp[i] < x, then update
//dp[i + 1] = min(dp[i + 1], x). 

//With this problem, instead of inserting a single x, we're inserting a range [l, r). It's much the same, we 
//look for the first time where dp[i] < l, but then we update everything past that like 
//dp[i + 1] = min(dp[i + 1], l), dp[i + 2] = min(dp[i + 2], l + 1), ..., dp[i + r] = min(dp[i + r], r - 1). 

//We can actually directly simulate this process using a ordered set. We just need to keep track of where the
//'segments' currently inside the dp array are starting and ending. And when we insert a segment, we just 
//replace r - l elements starting from l with elements in the range [l, r), and if there is excess, we can 
//update the answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    set<pll> s; //{pos, is start?}
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll l, r;
        cin >> l >> r;
        r ++;
        ll amt = r - l;
        ll lptr = l;
        while(amt != 0){
            ll nl, nr;
            auto ptr = s.upper_bound({lptr, 0});
            if(ptr == s.end()) break;
            nl = ptr->first;
            bool is_start = ptr->second;
            if(!is_start) {
                //abnormal, only can happen on first go
                nr = nl, nl = l;
                s.insert({nl, 0});
                s.insert({nl, 1});
            }
            else {
                ptr = s.upper_bound({nl, 2});
                nr = ptr->first;
            }
            lptr = nr;
            if(amt >= nr - nl) {    //can entirely replace
                s.erase({nl, 1});
                s.erase({nr, 0});
                amt -= nr - nl;
                continue;
            }
            //can't entirely replace
            s.erase({nl, 1});
            s.insert({nl + amt, 1});
            amt = 0;
        }
        ans += amt;
        s.insert({l, 1});
        s.insert({r, 0});
    }
    cout << ans << "\n";
    
    return 0;
}