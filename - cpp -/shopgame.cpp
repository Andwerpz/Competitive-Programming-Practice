#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1969D

//first, given that alice has already chosen her items, what does bob do? All bob can do is minimize how much money he gives
//to alice, so bob will greedily choose the items with the smallest values to buy, regardless of the amount of money alice
//may have spent on them. 

//this also implies that out of the elements that alice buys, bob will pick the k elements with the greatest b[i], and take
//them for free. Let's denote V as the minimum value of an item that bob takes for free. For a given V, how can alice maximize
//her profit? She must first pick k items that have b[i] >= V, and since those are the items that bob will pick for free, she
//wants to minimize the amount of money she spends on those items. Then, for every item that has b[i] < V, it's guaranteed that
//bob will buy it, so she should pick all items that will generate a profit, namely a[i] < b[i]. 

//Since any selection of items alice can make will have an associated value of V, it's sufficient to iterate through all possible
//values of V, compute the maximum profit for that V, and take the overall maximum. 

//optimization is left as an exercise to the reader :D

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<pair<ll, ll>> a(n);  //{alice, bob}
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        for(int i = 0; i < n; i++){ 
            cin >> a[i].second;
        }
        sort(a.begin(), a.end(), [](pair<ll, ll>& a, pair<ll, ll>& b) -> bool {
            if(a.second != b.second){
                return a.second > b.second;
            }
            return a.first > b.first;
        });
        ll ans = 0;
        ll paid_sum = 0;
        ll free_sum = 0;
        for(int i = 0; i < n; i++){
            paid_sum += max(0ll, a[i].second - a[i].first);
        }
        priority_queue<ll> q; //alice cost
        if(k == 0){
            ans = paid_sum;
        }
        for(int i = 0; i < n; i++){
            q.push(a[i].first);
            free_sum += a[i].first;
            if(q.size() > k){
                free_sum -= q.top();
                q.pop();
            }
            paid_sum -= max(0ll, a[i].second - a[i].first);
            if(q.size() == k){
                ans = max(ans, paid_sum - free_sum);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
