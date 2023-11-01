#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1890E1

//let's treat this like a segment sweepline problem. We'll sweepline from city 1 to city n, while keeping track of what days
//raining on the current city in a set. 

//First, we can keep track of for each day, the number of cities only that day rains on. 
//Second, for each city where there are exactly 2 days that rain on it, we'll store the pair in some sort of map. 
//then we'll track how many times each pair occurs. Note that there can only be a maximum of n unique pairs. 

//Then, the candidates for the pairs of days that we choose have to be among the pairs of days that we've seen while doing
//the sweepline; we can pretty easily calculate the answer for each of those pairs using the information we precomputed. 

//one edge case is choosing two days that are disjoint, but provide the maximum sum of individual rained on cities. 
    
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll t;
    cin >> t;
    while(t--){
        ll n, m, k;
        cin >> n >> m >> k;
        vector<pair<pair<ll, ll>, ll>> ends(0);
        for(ll i = 0; i < m; i++){
            ll l, r;
            cin >> l >> r;
            ends.push_back({{l, 1}, i});
            ends.push_back({{r + 1, -1}, i});
        }
        map<pair<ll, ll>, ll> mp;
        vector<ll> ind_mp(m, 0);
        set<ll> active;
        sort(ends.begin(), ends.end());
        ll p_time = 1;
        ll dry = n;
        for(ll i = 0; i < ends.size(); i++){
            ll cur_time = ends[i].first.first;
            bool is_end = ends[i].first.second == -1;
            ll ind = ends[i].second;
            if(active.size() >= 1) {
                dry -= cur_time - p_time;
            }
            if(active.size() == 1){
                ll a = *active.begin();
                ind_mp[a] += cur_time - p_time;
            }
            if(active.size() == 2){
                ll a = *active.begin();
                ll b = *active.rbegin();
                if(a > b) {
                    swap(a, b);
                }
                if(mp.find({a, b}) == mp.end()) {
                    mp.insert({{a, b}, 0});
                }
                mp[{a, b}] += cur_time - p_time;
            }
            if(is_end) {
                active.erase(ind);
            }
            else {
                active.insert(ind);
            }
            p_time = cur_time;
        }
        ll ans = 0;
        for(auto i = mp.begin(); i != mp.end(); i++){
            ll a = i -> first.first;
            ll b = i -> first.second;
            ll cur_ans = dry + i -> second;
            cur_ans += ind_mp[a];
            cur_ans += ind_mp[b];
            ans = max(ans, cur_ans);
        }
        sort(ind_mp.begin(), ind_mp.end());
        reverse(ind_mp.begin(), ind_mp.end());
        ans = max(ans, dry + ind_mp[0] + ind_mp[1]);
        cout << ans << "\n";
    }
    
    return 0;
}