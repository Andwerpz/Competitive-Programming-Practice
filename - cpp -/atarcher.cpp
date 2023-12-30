#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC131D

//Claim 1: it is never optimal to not tightly pack the arrows around the center; if we have a solution, 
//we can always improve it by tightly packing the arrows, and moving the arrows closer to the center. 

//let's say that we have our 'center' arrow at x = 0. If there are an even amount of arrows, we'll pick the 'left'
//arrow to be our 'center'. Then, we move all the arrows 1 unit to the left, and compute the new answer. 

//Claim 2: The optimal answer will always appear if you do this d times. This is kind of apparent when we take
//into consideration Claim 1, as if we do this more than d times, then we can always improve the answer by just moving 
//all the arrows closer to the center. 

//then, how to compute this? Note that each 'boundary' where if an arrow crosses it, the score changes, will only be
//crossed exactly once over the d shifts. Thus, for each boundary that can be crossed, we just compute at which shift
//it will be crossed, and what the score change is. 

//total complexity for this is O(m + d). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, d;
    cin >> n >> m >> d;
    vector<ll> r(m);
    vector<ll> s(m);
    cin >> r[0];
    for(int i = 0; i < m; i++){
        cin >> r[i];
    }
    for(int i = 0; i < m; i++){
        cin >> s[i];
    }
    ll ans = 0;
    ll cur_ans = 0;
    //compute initial score
    n --;
    cur_ans += s[0];
    ll x_left = -d;
    ll x_right = d;
    ll ptr_left = 0;
    ll ptr_right = 0;
    while(n != 0){
        //add to right
        while(ptr_right != m && r[ptr_right] < x_right) {
            ptr_right ++;
        }
        if(ptr_right != m){
            cur_ans += s[ptr_right];
        }
        x_right += d;
        n --;
        //add to left
        if(n != 0){
            while(ptr_left != m && -r[ptr_left] > x_left) {
                ptr_left ++;
            }
            if(ptr_left != m) {
                cur_ans += s[ptr_left];
            }
            x_left -= d;
            n --;
        }
    }
    x_left += d;
    x_right -= d;
    ans = cur_ans;
    //cout << "INIT ANS : " << ans << "\n";
    //sweep across d and take the maximum score
    priority_queue<pair<ll, pair<ll, ll>>> q;   //{-distance needed, {old val, new val}}
    for(int i = 0; i < m; i++){
        //left 
        {
            //cout << "LEFT : " << r[i] << "\n";
            ll x = (r[i] + 1);
            //find closest arrow to the right
            ll arrow = (x / d) * d;
            if(arrow == x) {
                arrow -= d;
            }
            arrow *= -1;
            x *= -1;
            if(arrow >= x_left) {
                ll dist = arrow - x;
                ll vold = s[i];
                ll vnew = 0;
                if(i != m - 1) {
                    vnew = s[i + 1];
                }
                q.push({-dist, {vold, vnew}});
            }
        }
        //right
        {
            //cout << "RIGHT : " << r[i] << "\n";
            ll x = r[i];
            //find closest arrow to the right
            ll arrow = (x / d) * d + d;
            if(arrow <= x_right) {
                ll dist = arrow - x;
                ll vold = 0;
                ll vnew = s[i];
                if(i != m - 1) {
                    vold = s[i + 1];
                }
                q.push({-dist, {vold, vnew}});
            }
        }
    }
    for(int i = 0; i < d; i++){
        while(q.size() != 0) {
            pair<ll, pair<ll, ll>> next = q.top();
            ll dist = -next.first;
            assert(dist > 0);
            assert(dist <= d);
            if(dist != i) {
                break;
            }
            q.pop();
            //cout << "CHANGE : " << dist << " " << next.second.first << " " << next.second.second << "\n";
            cur_ans += next.second.second - next.second.first;
        }
        //cout << "NEW ANS : " << cur_ans << "\n";
        ans = max(ans, cur_ans);
    }
    cout << ans << "\n";
    
    return 0;
}
