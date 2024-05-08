#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - F

//notice that we have to take all cupcakes of a specific value before taking any cupcakes of greater value. 

//for each value, keep a set of indexes where it appears. Then, along with our current position, we can determine
//the index of the last cupcake of that value that we'll take. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, set<int>> m;
        for(int i = 0; i < n; i++){
            m[a[i]].insert(i);
        }
        int ptr = 0;
        ll ans = 0;
        for(auto i = m.begin(); i != m.end(); i++){
            set<int> inds = i -> second;
            int tgt = -1;
            if(*inds.begin() >= ptr) {
                tgt = *inds.rbegin();
            }
            else {
                auto j = inds.lower_bound(ptr);
                j --;
                tgt = *j;
                tgt += n;
            }
            ans += tgt - ptr;
            ptr = tgt % n;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
