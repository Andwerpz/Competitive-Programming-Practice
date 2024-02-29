#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - crammingforfinals

//each person is relevant for at most 5000 rows, so for each row, we can track the ranges on the
//row in which each person is relevant for it. 

//then, we can simply do a sweepline across each row to get the minimum. 

//note that if there are more than 5 around million rows, then it's guaranteed that there exists a row
//that has a seat that is close to 0 students. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll r, c, d, n;
    cin >> r >> c >> d >> n;
    vector<pair<ll, ll>> a(n);
    set<pair<ll, ll>> v;
    for(int i = 0; i < n; i++){
        cin >> a[i].second >> a[i].first;
        v.insert(a[i]);
    }
    map<ll, vector<pair<ll, int>>> m;   //{row coord, {col, -1 or 1}}
    ld epsilon = 1e-10;
    for(int i = 0; i < n; i++){
        //circle center
        ll x = a[i].first;
        ll y = a[i].second;
        for(int j = max(1ll, y - d); j <= min(r, y + d); j++){
            if(!m.count(j)) {
                m[j] = vector<pair<ll, int>>(0);
            }
            ld h = abs(y - j);
            ld c_len = d * sin(acos(h / (ld) d));
            ll left = ceil((ld) x - c_len - epsilon) + epsilon;
            ll right = floor((ld) x + c_len + epsilon) + epsilon;
            left = max(1ll, left);
            right = min(c, right) + 1;
            m[j].push_back({left, 1});
            m[j].push_back({right, -1});
        }
    }
    if(m.size() != r) {
        cout << "0\n";
        return 0;
    }
    int ans = 1e9;
    for(auto i = m.begin(); i != m.end(); i++){
        sort(i -> second.begin(), i -> second.end());
        int cnt = 0;
        if(i -> second[0].first != 1){
            ans = min(ans, 0);
        }
        if(i -> second.rbegin() -> first != c + 1) {
            ans = min(ans, 0);
        }
        for(int j = 0; j < i -> second.size() && i -> second[j].first <= c; j++){
            cnt += i -> second[j].second;
            if(i -> second[j].first != i -> second[j + 1].first && !v.count({i -> second[j].first, i -> first})) {
                ans = min(ans, cnt);
            }
        }
    }   
    cout << ans << "\n";
    
    return 0;
}
