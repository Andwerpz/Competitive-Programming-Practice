#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest I

//sort the players by age, and consider the segments independently. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    set<pair<ll, bool>> s;  //age, is catfish
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll age;
        cin >> age;
        char cat;
        cin >> cat;
        s.insert({age, cat == 'C'});
        ans += (cat == 'L');
    }
    if(!s.begin() -> second) {
        ans += (s.begin() -> first) - 17;
    }
    if(!s.rbegin() -> second) {
        ans += ((ll) 1e9) - s.rbegin() -> first;
    }
    for(auto i = s.begin(); i -> first != s.rbegin() -> first; i++){
        auto ptr = i;
        ptr ++;
        ll cur = i -> first;
        bool cur_c = i -> second;
        ll next = ptr -> first;
        bool next_c = ptr -> second;
        ll diff = next - cur - 1;
        assert(diff >= 0);
        if(next_c && cur_c) {
            //do nothing
        }
        else if(!next_c && !cur_c) {
            ans += diff;
        }
        else {
            ans += diff / 2;
        }
    }
    assert(ans >= 0);
    cout << ans << "\n";
    
    return 0;
}
