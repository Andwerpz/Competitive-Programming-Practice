#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 878B

//turns out solution is just a bunch of casework. 

//the problem gives us in the statement that the order in which we create the groups should not affect the outcome.
//so, the first thing we can do is create any groups possible within the individual buses. 

//next, we consider what happens when we concatenate buses. Concatenating a bus with another one is the same as
//taking from the front and back of one bus simultaneously. So, for the reduced bus, we see how many groups we
//can make by taking from the front and back. 

//there are 3 major cases:
//1. we can eliminate the entire bus
//since concatenating two busses in this case will just annihilate both of them, then we only care about the parity of
//the number of buses. 

//2. we can eliminate all but one contiguous section of people from the same city in the middle. 
//in this case, the middle sections that 'pile up' will themselves eventually annihilate. If the middle
//sections perfectly annihilate, then the remaining borders on the extreme left and right will annihilate as
//well. 

//3. we can't eliminate any more than the other two cases. 
//in this case, the middles of each bus will 'pile up' as we concatenate them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k, m;
    cin >> n >> k >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    stack<pair<int, int>> s;
    for(int i = 0; i < n; i++){
        if(s.size() != 0 && s.top().first == a[i]) {
            s.top().second ++;
        }
        else {
            s.push({a[i], 1});
        }
        if(s.top().second == k){
            s.pop();
        }
    }
    ll tot = 0;
    vector<pair<int, int>> g(0);
    while(s.size() != 0){
        tot += s.top().second;
        g.push_back(s.top());
        s.pop();
    }
    bool mid_rem = false;
    ll border = 0;
    for(int i = 0; i < g.size(); i++){
        int l = i;
        int r = g.size() - 1 - i;
        if(r <= l) {
            if(g.size() % 2 == 1){
                mid_rem = true;
            }
            break;
        }
        if(g[l].first != g[r].first) {
            break;
        }
        if(g[l].second + g[r].second < k){
            break;
        }
        border += k;
        if(g[l].second + g[r].second > k){
            break;
        }
    }
    ll ans = 0;
    if(border == tot) {
        if(m % 2 == 0){
            ans = 0;
        }
        else {
            ans = tot;
        }
    }
    else if(mid_rem) {
        ll rem = (g[g.size() / 2].second * m) % k;
        if(rem != 0){
            ans = rem + border;
        }
        else {
            ans = 0;
        }
    }
    else {
        ll mid = tot - border;
        ans = mid * m + border;
    }
    cout << ans << "\n";
    
    return 0;
}
