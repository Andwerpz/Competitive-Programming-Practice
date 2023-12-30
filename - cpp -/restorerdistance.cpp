#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1355E

//first, we can make m = min(m, a + r). 

//next, given some target height, we can compute the cost required to make all pillars equal to the target height in
//linear time. 

//then, we can ternary search for the minimum cost over all target heights. 

//one thing i didn't prove when solving is whether or not the distance is a bitonic function. 

ll calcDist(ll n, ll a, ll r, ll m, ll tgt, vector<ll>& h) {
    ll nr_remove = 0;
    ll nr_add = 0;
    for(int i = 0; i < n; i++){
        if(h[i] <= tgt) {
            nr_add += tgt - h[i];
        }
        else {
            nr_remove += h[i] - tgt;
        }
    }
    ll nr_move = min(nr_add, nr_remove);
    nr_add -= nr_move;
    nr_remove -= nr_move;
    return nr_add * a + nr_remove * r + nr_move * m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, a, r, m;
    cin >> n >> a >> r >> m;
    m = min(m, a + r);
    vector<ll> h(n);
    for(int i = 0; i < n; i++){
        cin >> h[i];
    }
    sort(h.begin(), h.end());
    ll low = h[0];
    ll high = h[n - 1];
    while(high - low > 10) {
        ll m1 = low + (high - low) / 3 * 1;
        ll m2 = low + (high - low) / 3 * 2;
        ll m1_dist = calcDist(n, a, r, m, m1, h);
        ll m2_dist = calcDist(n, a, r, m, m2, h);
        if(m1_dist == m2_dist) {
            low = m1;
            high = m2;
        }
        else if(m1_dist < m2_dist) {
            high = m2;
        }
        else {
            low = m1;
        }
    }
    ll ans = calcDist(n, a, r, m, low, h);
    for(int i = low + 1; i <= high; i++){
        ans = min(ans, calcDist(n, a, r, m, i, h));
    }
    cout << ans << "\n";
    
    return 0;
}
