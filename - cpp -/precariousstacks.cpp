#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 M

//if the range on x were smaller, you could use a lazy segtree with max range query and 
//range assignment. 

//use a map to keep track of the endpoints where each height starts and stops. When adding in a new square, 
//the new height along the segment is simply the maximum height along the segment in the square, plus the size
//of the square. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll ans = 0;
    map<ll, ll> m;
    m.insert({1e10, 0});
    m.insert({-1, 0});
    for(int i = 0; i < n; i++){
        ll x, s;
        cin >> x >> s;
        ll ptr = x;
        ll bot = 0;
        while(m.size() != 0 && m.rbegin() -> first >= ptr && ptr < x + s) {
            ptr = m.lower_bound(ptr) -> first;
            bot = max(bot, m.find(ptr) -> second);
            if(ptr >= x + s){
                break;
            }
            m.erase(ptr);
            ptr ++;
        }
        ans = max(ans, bot + s);
        m.insert({x - 1, (--m.upper_bound(x)) -> second});
        m.insert({x + s, m.lower_bound(x + s) -> second});
        m.insert({x, bot + s});
        m.insert({x + s - 1, bot + s});
        cout << ans << "\n";
    }
    
    return 0;
}

