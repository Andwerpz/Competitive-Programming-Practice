#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<ll>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __ll128 lll;
// typedef __float128 lld;

//2025 NAQ - H

//observe that an optimal solution will always move people in one direction only. 
//intuition here is that we always want to move the heaviest person, as we'll have to move them the least
//in order to change the torque the most

//we move them until they hit another person, at which point they merge. Now their 'weight' is the sum
//of weights divided by the number of people that were merged. 

//just greedily pick the best person to move at every step. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n; cin >> n;
    vector<array<ll,2>> a(n);
    ll t = 0;

    for(ll i = 0; i < n; i++) {
        ll p, w; cin >> p >> w;
        a[i] = {p, w};
        t += p * w;
    }

    if(t > 0) {
        for(auto &x : a) {
            x[0] *= -1;
        }
    }

    t = abs(t);

    priority_queue<pair<ld, array<ll,2>>> pq; //{cost to move per unit, pos}
    map<ll, array<ll,3>> m; // {pos, {edit time, #ppl, sum weights}}

    for(ll i = 0; i < n; i++) {
        auto [p, w] = a[i];
        pq.push({w, {p, 0}});
        m[p] = {0, 1, w};
    }

    //add thing at the end 
    m[1e18] = {0,0,0}; //inf next pos

    ld res = 0;
    ll ptr = 1;

    while(pq.size()) {
        auto [cpu, info] = pq.top();
        pq.pop();

        auto [pos, edit_time] = info;
        if(m.count(pos) == 0) continue;
        auto [medit, ppl, s] = m[pos];

        // cout << "cpu : " << cpu << " pos : " << pos << " edit_time : " << edit_time << '\n';
        // cout << "medit : " << medit << " ppl : " << ppl << " s : " << s << '\n';

        if(medit != edit_time) {
            continue;
        }

        ld max_move = ((ld)t ) / (s);
        ll next_pos = (*m.upper_bound(pos)).first;
        ll max_dist = (next_pos - pos);

        if(max_move <= max_dist) {
            res += max_move * ppl;
            break;
        }

        //we are able to move max_dist.
        res += max_dist * ppl;
        t -= s * max_dist;

        //merge to the next
        m[next_pos][0] = ptr;
        m[next_pos][1] += ppl;
        m[next_pos][2] += s;

        m.erase(pos);

        pq.push({((ld) m[next_pos][2]) / m[next_pos][1], {next_pos, ptr}});
        ptr++;
    }

    cout << fixed << setprecision(10) << res << '\n';
    
    return 0;
}