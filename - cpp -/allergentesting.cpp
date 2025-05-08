#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//ICPC NAC 2023 - A

//let dp[s][d] = maximum number of compounds you can test given that you have s sites and d days. 
//Suppose that you put each compound on one site. Whichever site flares up, you'll have s - 1 sites
//and d - 1 days left, so dp[s][d] += s * dp[s - 1][d - 1]. 

//but you don't have to limit yourself to putting a compound on only one site. If you have another
//batch on compounds and you put each of them on two sites, if two sites flare up, you can identify
//which compounds have been put exactly on those two sites and narrow down the search. So
//dp[s][d] += \binom{s, 2} dp[s - 2][d - 1]. 

//so in general, dp[s][d] = \sum_{i = 0}^{n} \binom{s}{i} dp[s - i][d - 1]

//actually, if you brute force compute some values, you'll find that dp[s][d] = (d + 1)^s. 
//isn't this convenient :/

//so all that's left to do is binary search across s to see what's the minimum s that you can 
//do n sites. To compare very large (d + 1)^s to n, you can use the fact that 
//log((d + 1)^s) = log(d + 1) * s and compare it to log(n).

ld epsilon = 1e-9;

ll binexp(ll a, ll b) {
    ll ans = 1, pow = a;
    while(b != 0) {
        if(b % 2) ans *= pow;
        pow *= pow;
        b /= 2;
    }
    return ans;
}

//returns n > (d + 1)^s
bool is_bigger(ll n, ll s, ll d) {
    // cout << log(n) << " " << log(d + 1) * s << "\n";
    if(abs(log(n) - log(d + 1) * s) < epsilon) return n > binexp(d + 1, s);
    return log(n) > log(d + 1) * s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    //dp[s][d] = (d + 1)^s
    int t;
    cin >> t;
    while(t--){
        ll n, d;
        cin >> n >> d;
        ll low = 0, high = 1e18;
        ll ans = high;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if(is_bigger(n, mid, d)) low = mid + 1;
            else high = mid - 1, ans = mid;
        }
        cout << ans << "\n";
    }

    return 0;
}