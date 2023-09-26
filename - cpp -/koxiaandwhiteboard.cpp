#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void insert(map<ll, ll>& mp, ll val) {
    if(mp.find(val) == mp.end()) {
        mp.insert({val, 0});
    }
    mp[val] ++;
}

void erase(map<ll, ll>& mp, ll val) {
    mp[val] --;
    if(mp[val] == 0){
        mp.erase(val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        map<ll, ll> mp;
        for(int i = 0; i < n; i++){
            ll val;
            cin >> val;
            insert(mp, val);
        }
        for(int i = 0; i < m; i++){
            ll val;
            cin >> val;
            erase(mp, mp.begin() -> first);
            insert(mp, val);
        }
        ll ans = 0;
        for(auto i = mp.begin(); i != mp.end(); i++){
            ans += i -> first * i->second;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
