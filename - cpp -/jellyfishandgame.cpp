#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1875B

//hah
// - 10/03/2023 andrew

//once i assumed that the optimal strategy is to trade your minimum value for your opponent's maximum value, this 
//problem becomes trivial. 

//how to prove that this strategy is optimal, i have no idea. 

void insert(map<ll, ll>& m, ll val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

void erase(map<ll, ll>& m, ll val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

//it's a's turn. Returns the gain for a
ll do_op(map<ll, ll>& a, map<ll, ll>& b) {
    ll mn = a.begin() -> first;
    ll mx = b.rbegin() -> first;
    if(mx <= mn) {
        return 0;
    }
    erase(a, mn);
    erase(b, mx);
    insert(a, mx);
    insert(b, mn);
    return mx - mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        ll ans = 0;
        map<ll, ll> a, b;
        for(int i = 0; i < n; i++){
            ll next;
            cin >> next;
            ans += next;
            insert(a, next);
        }
        for(int i = 0; i < m; i++){
            ll next;
            cin >> next;
            insert(b, next);
        }
        ans += do_op(a, b);
        if(k == 1){
            cout << ans << "\n";
            continue;
        }
        ans -= do_op(b, a);
        if(k % 2 == 1){
            ans += do_op(a, b);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
