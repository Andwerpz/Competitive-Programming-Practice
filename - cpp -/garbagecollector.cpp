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

//AtCoder - AGC27B

//First, observe that if we want to take multiple pieces of trash at once, we always want to first travel to the 
//furthest piece, and then take them as we travel back to the trash bin. Any other way of picking up multiple pieces
//will only result in more cost. 

//Next, given two pieces of trash at locations x_0 and x_1, in what case would we actually want to pick them up
//at the same time? If we only consider the cost of moving around, then picking up one at a time would give cost
//5x_0 + 5x_1, and picking them up at the same time would give cost x_1 + 4(x_1 - x_0) + 9x_0 = 5x_0 + 5x_1. So
//in the case of two pieces of trash, it's the same. However, for 3 pieces of trash, we get 7x_0 + 5x_1 + 5x_2, 
//and the pattern continues like this. 

//Why would we ever want to group up multiple pieces of trash? Well, although the travel cost will be increasing, 
//the amount of times we have to put down trash will be decreasing. So if the put down cost is sufficiently
//high, then it might be worth it to group up trash putdowns. 

//Given a fixed amount of trash putdowns, how do we compute the minimum cost? Well, first observation is that 
//we want the higher multipliers on the smaller distances. From that, we can observe that we want to also make
//the groups as evenly sized as possible. This is to minimize the multipliers. Since the cost as a function of the
//number of putdowns is bitonic, we can just ternary search for the minimum cost. 

ll calc_ans(ll n, ll x, vl& a, ll take_amt) {
    ll ans = (take_amt + n) * x;    //need to at least pick up every piece of trash, and then desposit them. 
    for(int i = 0; i < n; i++){
        ll mult = 5;
        if(i >= take_amt) mult += 2 * ((i - take_amt) / take_amt);
        ans += a[n - 1 - i] * mult;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, x;
    cin >> n >> x;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int low = 1;
    int high = n;
    while(high - low > 20) {
        int m0 = low + (high - low) * 1 / 3;
        int m1 = low + (high - low) * 2 / 3;
        ll v0 = calc_ans(n, x, a, m0);
        ll v1 = calc_ans(n, x, a, m1);
        if(v0 < v1) {
            high = m1;
        }
        else {
            low = m0;
        }
    }
    ll ans = 1e18;
    for(int i = low; i <= high; i++){
        ans = min(ans, calc_ans(n, x, a, i));
    }
    cout << ans << "\n";
    
    return 0;
}