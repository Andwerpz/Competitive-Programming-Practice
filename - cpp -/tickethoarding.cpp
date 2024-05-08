#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1951C

//note that you always want to buy tickets in bulk, and you always should pick the ceil(k / m) days with the
//minimum base cost to buy. 

//if k % m == 0, then the answer is pretty easy, just buy m tickets on each of the days. 

//otherwise, you have a remainder, k % m. Just try for each of the days you buy, assigning the remainder to that day.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m, k;
        cin >> n >> m >> k;
        ll nr_take = (k / m) + (k % m != 0);
        vector<pair<ll, pair<int, int>>> a(n);
        vector<ll> b(0);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
            a[i].second.first = i;
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < n; i++){
            a[i].second.second = i;
        }
        sort(a.begin(), a.end(), [](auto a, auto b) -> bool {
            return a.second.first < b.second.first;
        });
        for(int i = 0; i < n; i++){
            if(a[i].second.second < nr_take) {
                b.push_back(a[i].first);
            }
        }
        n = nr_take;
        ll ans = 1e18;
        if(k % m == 0){
            //ans is predetermined
            ans = 0;
            ll b_sum = 0;
            for(int i = 0; i < n; i++){  
                ans += m * (b[i] + b_sum);
                b_sum += m;
            }
            cout << ans << "\n";
            continue;
        }
        //calc initial ans
        ll rem = k % m;
        {
            ll b_sum = rem;
            ans = rem * b[0];
            for(int i = 1; i < n; i++){
                ans += m * (b[i] + b_sum);
                b_sum += m;
            }
        }
        //assign rem to other stuff
        ll diff = m - rem;
        ll p_ans = ans;
        for(int i = 1; i < n; i++){
            ll n_ans = p_ans;
            ll b0_cost = b[i - 1] + m * (i - 1);
            ll b1_cost = b[i] + m * (i - 1) + rem;
            ll b1_ncost = b[i] + m * i;
            n_ans -= b0_cost * rem;
            n_ans -= b1_cost * m;
            n_ans += b0_cost * m;
            n_ans += b1_ncost * rem;
            ans = min(ans, n_ans);
            p_ans = n_ans;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
