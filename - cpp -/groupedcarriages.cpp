#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//COMPFEST 15 G

//binary search over how many people to put in each carriage.

//to test whether an amount of people works, we can go from the leftmost carriage to the right one. 
//each carriage has a start point and end point that you can precompute. 
//use a priority queue to prioritize carriages with close endpoints over far ones. 

bool solve(int n, vector<ll>& a, vector<ll>& d, vector<vector<int>>& sd, ll val) {
    priority_queue<pair<ll, pair<int, ll>>> q;  //{-(i + d), {-i, nr people left}}
    for(int i = 0; i < n; i++){
        for(int j = 0; j < sd[i].size(); j++){
            int next = sd[i][j];
            if(a[next] == 0){
                continue;
            }
            q.push({-(next + d[next]), {-next, a[next]}});
        }
        ll rem = val;
        while(q.size() != 0 && rem != 0){
            int cur = -q.top().second.first;
            ll cur_end = -q.top().first;
            ll cur_amt = q.top().second.second;
            q.pop();
            if(i > cur_end) {
                return false;
            }
            ll change = min(cur_amt, rem);
            cur_amt -= change;
            rem -= change;
            if(cur_amt != 0){
                q.push({-cur_end, {-cur, cur_amt}});
            }
        }
    }
    return q.size() == 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n), d(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> d[i];
    }
    vector<vector<int>> sd(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        int start = max(0ll, i - d[i]);
        sd[start].push_back(i);
    }
    ll ans = 1e18;
    ll low = 0;
    ll high = 1e18;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(solve(n, a, d, sd, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
