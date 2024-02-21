#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - E

//first part of the question is figuring out the expiration time for each pizza. 
//note that we either want to maximize the amount of internal or crust edges we choose. 

//after we've found the expiration date for each pizza, it's just a scheduling problem; we want to maximize
//the value of the pizza that we take. 
//to solve scheduling problem, we can use a greedy algorithm. Sort all the pizzas in ascending order
//according to their expiration date. 

//if a pizza expires at time t, and has value v, we know that before this pizza expires, we can eat at 
//most t other pizzas. If, in those t pizzas, there exists a pizza that has less value than v, we instead 
//want to eat this current pizza in it's place. 

//thus, we just keep a min priority queue to keep track of the pizzas that we're eating, and add the
//pizzas to the queue if there is extra room, or if the minimum pizza in the queue is smaller than the 
//current value. 

//another way is to just sort the pizzas in descending order by value, and for each, greedily find the latest
//time at which we can eat it. We can keep track of the time we still have using a set. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(4)); //{s, q, c, v}
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            cin >> a[i][j];
        }
    }
    vector<pair<ll, ll>> q(n);  //{time, wasted value}
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll s = a[i][0];
        ll _q = a[i][1];
        ll c = a[i][2];
        ll d = min(s * _q, (s - 1) * c + _q);
        q[i].first = d;
        q[i].second = a[i][3];
        ans += a[i][3];
    }
    sort(q.begin(), q.end(), [](pair<ll, ll> a, pair<ll, ll> b) -> bool {
        return a.second > b.second;
    }); 
    set<int> unv;
    for(int i = 0; i < 2 * 1e6; i++){
        unv.insert(i);
    }
    for(int i = 0; i < q.size(); i++){
        int time = q[i].first - 1;
        ll value = q[i].second;
        if(time < *unv.begin()) {
            continue;
        }
        ans -= value;
        auto j = unv.upper_bound(time);
        j --;
        unv.erase(j);
    }
    cout << ans << "\n";
    
    return 0;
}
