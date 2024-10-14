#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2003D2

//read easy version comments for context. 

//as we can only use each sequence once, we can't always raise everything to max_mex. 
//however, if there is a repeated m1, then whatever is reachable from that m1, we can always get. 

//for each m1, we'll precompute what's the maximum m2 that is reachable from that m1, and we'll also
//precompute a 'base', something that is reachable from any starting m due to having a duplicate m1 
//as a starting point. 

//then, we can iterate through all m1 in ascending order. If there is a stretch with no m1, we can do some
//casework:
//ptr < base: just assign base 
//else, ptr >= base: just assign ptr. 

ll arith_sum(ll start, ll nr_elem, ll inc) {
    ll ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

ll calc_mex(vl& a){
    sort(a.begin(), a.end());
    if(a[0] != 0){
        return 0;
    }
    for(int i = 1; i < a.size(); i++){
        if(a[i] - 1 > a[i - 1]) {
            return a[i - 1] + 1;
        }
    }
    return a[a.size() - 1] + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        map<ll, ll> mx_obtain, m1_cnt;
        vector<pll> mxa(n);
        for(int i = 0; i < n; i++){
            int len;
            cin >> len;
            vl a(len);
            for(int j = 0; j < len; j++){
                cin >> a[j];
            }
            ll m1 = calc_mex(a);
            a.push_back(m1);
            ll m2 = calc_mex(a);
            mxa[i] = {m1, m2};
            // cout << "M1 M2 : " << m1 << " " << m2 << "\n";
        }
        sort(mxa.begin(), mxa.end());
        reverse(mxa.begin(), mxa.end());
        for(int i = 0; i < n; i++){
            ll m1 = mxa[i].first;
            ll m2 = mxa[i].second;
            mx_obtain[m1] = max({mx_obtain[m1], mx_obtain[m2], m2});
            m1_cnt[m1] ++;
            // cout << "SET MX OBTAIN : " << m1 << " " << m2 << " " << mx_obtain[m1] << "\n";
        }
        ll base = 0;
        for(auto i = m1_cnt.begin(); i != m1_cnt.end(); i++){
            if(i->second > 1){
                base = max(base, mx_obtain[i->first]);
            }
            if(i->second != 0){
                base = max(base, i->first);
            }
        }
        // cout << "BASE : " << base << "\n";
        ll ans = 0;
        ll ptr = 0;
        while(ptr <= m) {
            // cout << "PTR : " << ptr << endl;
            if(m1_cnt[ptr] != 0){
                // cout << "INC ANS : " << max({ptr, base, mx_obtain[ptr]}) << "\n";
                // cout << "MX OBTAIN : " << mx_obtain[ptr] << "\n";
                ans += max({ptr, base, mx_obtain[ptr]});
                ptr ++;
                continue;
            }
            ll next = m + 1;
            if(base + 1 > ptr){
                next = min(next, base + 1);
            }
            if(m1_cnt.rbegin()->first > ptr) {
                // cout << "NEXT RBEGIN : " << m1_cnt.upper_bound(ptr)->first << "\n";
                next = min(next, m1_cnt.upper_bound(ptr)->first);
            }
            ll diff = next - ptr;
            if(ptr > base) {
                // cout << "ADD ARITH SUM" << "\n";
                ans += arith_sum(ptr, diff, 1);
            }
            else {
                // cout << "ADD BASE" << "\n";
                ans += base * diff;
            }
            ptr = next;
        }
        cout << ans << "\n";
    }
    
    return 0;
}