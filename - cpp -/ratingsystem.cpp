#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1845D

//turn a[i] from a difference array, into an absolute rating array. In other words, a[i] = pfx_sum(a, i), where
//pfx_sum(int[], int) computes the sum of the given int[] in the segment [0, i]. 

//we can try k = a[i] for all i, and one of the k should give us the maximum answer. 
//note that if an a[i] appears twice, we always take the lower indexed one. 

//if we set k, the maximum 'increase' in rating compared to if there were no k is the maximum amount that the rating 
//dips below k. 

//we can use a suffix minimum array to find the minimum dipping below k. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<ll> a(n + 1);
        n ++;
        set<pair<ll, ll>> valley;
        for(int i = 1; i < n; i++){
            cin >> a[i];
            a[i] += a[i - 1];
        }
        for(int i = 1; i < n; i++){
            bool greater = false;
            if(i != n - 1 && a[i] > a[i + 1]){
                greater = true;
            }
            if(a[i] > a[i - 1]){
                greater = true;
            }
            if(!greater) {
                valley.insert({a[i], i});
            }
        }
        ll ans = -1e18;
        ll ansk = -1;
        ll pmax = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] < pmax) {
                continue;
            }
            pmax = a[i];
            while(valley.size() != 0 && valley.begin() -> second < i) {
                valley.erase(valley.begin());
            }
            ll val = a[i];
            if(valley.size() != 0){
                val = valley.begin() -> first;
            }
            ll inc = a[i] - val;
            ll nans = a[n - 1] + inc;
            if(nans > ans){
                ans = nans;
                ansk = a[i];
            }
        }
        cout << ansk << "\n";
    }
    
    return 0;
}
