#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1877B

//just greedily try to pay the least amount of money possible. 

void insert(map<ll, int>& m, ll val, int amt) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] += amt;
}

void erase(map<ll, int>& m, ll val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll p;
        cin >> n >> p;
        map<ll, int> m;
        ll ans = 0;
        vector<pair<ll, int>> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i].second;
        }
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        sort(a.begin(), a.end());
        insert(m, p, n);
        for(int i = 0; i < n; i++){
            ans += m.begin()->first;
            //cout << "BUY : " << m.begin() -> first << "\n";
            erase(m, m.begin() -> first);
            insert(m, a[i].first, a[i].second);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
