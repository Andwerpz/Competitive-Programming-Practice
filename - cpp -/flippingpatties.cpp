#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

void insert(map<int, int>& m, int val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> m;
    for(int i = 0; i < n; i++){
        int d, t;
        cin >> d >> t;
        insert(m, t);
        insert(m, t - d);
        insert(m, t - d * 2);
    }
    int ans = 0;
    for(auto i = m.begin(); i != m.end(); i++){
        ans = max(ans, i -> second);
    }
    ans = (ans + 1) / 2;
    cout << ans << "\n";
    
    return 0;
}
