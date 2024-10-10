#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2024 ICPC Asia Pacific Championship - C

int bit_cnt(ll val) {
    return __builtin_popcountll(val);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n == 1){
            if(a[0] == 0){
                cout << "0\n";
            }
            else {
                cout << (1ll << a[0]) - 1ll << "\n";
            }
            continue;
        }
        if(n == 2 && a[0] + 1 == a[1]) {
            cout << (1ll << (a[0] + 1)) - 2 << "\n";
            continue;
        }
        int big_drop = -1;
        int drop_ind = -1;
        for(int i = 1; i < n; i++){
            int cur = a[i - 1] - a[i];
            if(cur > big_drop) {
                big_drop = cur;
                drop_ind = i;
            }
        }
        if(big_drop == -1){
            cout << "-1\n";
            continue;
        }
        if(a[drop_ind] == 0){
            cout << "-1\n";
            continue;
        }
        ll start = (1ll << (ll) (big_drop + 1));
        int tmp = big_drop + 1;
        while(bit_cnt(start) != a[drop_ind]) {
            // cout << "TMP : " << tmp << endl;
            start |= (1ll << (ll) (tmp + 1));
            tmp ++;
        }
        start -= drop_ind;
        if(start < 0 || a[0] != bit_cnt(start)){
            cout << "-1\n";
            continue;
        }
        ll ans = start;
        bool is_valid = true;
        for(int i = 1; i < n; i++){
            start ++;
            if(a[i] != bit_cnt(start)) {
                is_valid = false;
                break;
            }
        }
        cout << (is_valid? ans : -1) << "\n";
    }
    
    return 0;
}
