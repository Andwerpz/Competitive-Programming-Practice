#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//USACO 2023 December Contest, Gold P3

//given a y value, and (a, b) pair, we can find the cost in log(n) time if we precompute two arrays; l_sum and r_sum.
//l_sum[i] gives us the sum of distances of the elements to the left of x[i]. r_sum stores similar information but to the right. 

//to solve a query independently, we can just ternary search for the best y value. l_sum and r_sum don't change.

//total complexity is O(n + q * log(n)^2)

ll calcDist(vector<ll>& x, vector<ll>& l_sum, vector<ll>& r_sum, ll a, ll b, ll y) {
    ll low = 0;
    ll high = x.size() - 1;
    ll ind = 0;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(x[mid] <= y) {
            ind = max(ind, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    ll ans = (l_sum[ind] + (y - x[ind]) * (ind + 1)) * a;
    if(ind != x.size() - 1) {
        ans += (r_sum[ind + 1] + (x[ind + 1] - y) * (x.size() - 1 - ind)) * b;
    }
    return ans;
}

ll solve(vector<ll>& x, vector<ll>& l_sum, vector<ll>& r_sum, ll a, ll b) {
    ll low = x[0];
    ll high = x[x.size() - 1];
    while(high - low > 5) {
        ll m1 = low + (high - low) / 3 * 1;
        ll m2 = low + (high - low) / 3 * 2;
        ll m1_dist = calcDist(x, l_sum, r_sum, a, b, m1);
        ll m2_dist = calcDist(x, l_sum, r_sum, a, b, m2);
        if(m1_dist <= m2_dist) {
            high = m2;
        }
        if(m2_dist <= m1_dist) {
            low = m1;
        }
    }
    ll ans = calcDist(x, l_sum, r_sum, a, b, low);
    for(int i = low + 1; i <= high; i++){
        ans = min(ans, calcDist(x, l_sum, r_sum, a, b, i));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> x(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }
    sort(x.begin(), x.end());
    vector<ll> l_sum(n, 0), r_sum(n, 0);
    for(int i = 1; i < n; i++){
        l_sum[i] = l_sum[i - 1] + (x[i] - x[i - 1]) * (i);
    }
    for(int i = n - 2; i >= 0; i--){
        r_sum[i] = r_sum[i + 1] + (x[i + 1] - x[i]) * (n - 1 - i);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        ll a, b;
        cin >> a >> b;
        cout << solve(x, l_sum, r_sum, a, b) << "\n";
    }
    
    return 0;
}
