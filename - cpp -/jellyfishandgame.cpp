#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1875B

//hah

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        map<ll, ll> a;
        map<ll, ll> b;
        int n, m, k;
        cin >> n >> m >> k;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            insert(a, next);
        }
        for(int i = 0; i < m; i++){
            int next;
            cin >> next;
            insert(b, next);
        }
        for(int i = 1; i <= k; i++){
            if(i % 2 == 1){
                ll mn = a.begin() -> first;
                ll mx = b.rbegin() -> first;
                if(mn < mx) {
                    erase(a, mn);
                    insert(a, mx);
                    erase(b, mx);
                    insert(b, mn);
                }
            }
            else {
                ll mn = b.begin() -> first;
                ll mx = a.rbegin() -> first;
                if(mn < mx) {
                    erase(b, mn);
                    insert(b, mx);
                    erase(a, mx);
                    insert(a, mn);
                }
            }
        }
        ll ans = 0;
        for(auto i = a.begin(); i != a.end(); i++){
            ans += i -> first * i -> second;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
