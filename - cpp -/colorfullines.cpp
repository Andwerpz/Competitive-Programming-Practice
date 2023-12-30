#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC130B

//just simulate it backwards, and keep track of how many rows and columns have been painted already. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll h, w, c, q;
    cin >> h >> w >> c >> q;
    vector<ll> ans(c, 0);
    vector<vector<ll>> queries(q, vector<ll>(3, 0));
    for(int i = 0; i < q; i++){
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }
    set<ll> vr, vc;
    for(int i = q - 1; i >= 0; i--){
        ll t = queries[i][0];
        ll n = queries[i][1];
        ll color = queries[i][2];
        n --;
        color --;
        if(t == 1){
            //paint squares in nth row
            if(vr.find(n) != vr.end()) {
                continue;
            }
            ans[color] += w - vc.size();
            vr.insert(n);
        }
        else {
            //paint squares in nth column
            if(vc.find(n) != vc.end()) {
                continue;
            }
            ans[color] += h - vr.size();
            vc.insert(n);
        }
    }
    for(int i = 0; i < c; i++){
        cout << ans[i] << " \n"[i == c - 1];
    }
    
    return 0;
}
