#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1890D

//first note that it's optimal to connect everything to city 1. If you connect two other cities, lets say a and b,
//you might as well just connect a to 1, then b to 1. 

//then, we just have to check if it's possible to connect all cities, in some order, to 1. Note that the total population
//sum to connect city i to 1 is equal to i * c. So, we just want to greedily connect whatever city we can, because connecting
//it will only increase the sum of population in the connected component connected to 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll c;
        cin >> n >> c;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll sum = a[0];
        vector<pair<ll, ll>> cost(0);
        for(int i = 1; i < n; i++){
            ll cur_cost = (ll) (i + 1ll) * c - a[i];
            cost.push_back({cur_cost, i});
        }
        sort(cost.begin(), cost.end());
        bool is_valid = true;
        for(int i = 0; i < cost.size(); i++) {
            if(sum < cost[i].first) {
                is_valid = false;
                break;
            }
            sum += a[cost[i].second];
        }
        cout << (is_valid? "Yes" : "No") << "\n";
    }
    
    return 0;
}
