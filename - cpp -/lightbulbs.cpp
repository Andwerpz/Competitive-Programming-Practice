#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1914G1, G2

//each color of lightbulb forms a segment. Note that if we turn on a segment, then we can use the operations
//to turn on any segment that intersects this segment. 

//For example: if we turn on the '1' segment, we can turn on the '2' segment as well. 
//1 2 1 2

//but, if a segment completely contains another segment, then turning on the inside segment will not allow you
//to directly turn on the outside segment. But it could be the case that another segment acts as a bridge between the
//two.

//Turning on the '2' segment can allow you to turn on the '1' segment, due to the position of the '3' segment. 
//1 2 3 2 1 3

//to find the minimum amount of initial lightbulbs, we want to first combine all the segments as much as possible
//then the number of connected components is equal to the initial amount of lightbulbs. 

//for each connected component, there will be some number of lightbulbs we can initially turn on to turn the entire 
//component on. The number of combinations is simply the product of all the components. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < 2 * n; i++){
            t[i] = uneut;
        }
    }

    void build() { // build the tree after manually assigning the values.
        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) { // sum on interval [l, r)
        T res = qneut;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                res = fcombine(res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res = fcombine(res, t[r]);
            }
        }
        return res;
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> c(2 * n);
        for(int i = 0; i < 2 * n; i++){
            cin >> c[i];
            c[i] --;
        }
        vector<int> sec(n, -1);
        vector<int> fir(n, -1);
        for(int i = c.size() - 1; i >= 0; i--) {
            if(sec[c[i]] == -1){
                sec[c[i]] = i;
            }
            fir[c[i]] = i;
        }
        //assignment modify, max query
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        Segtree<int> segt(2 * n, 1e9, 1e9, fmodify, fcombine); 
        vector<int> seg_gid(n, -1);
        vector<vector<int>> seg_g(0);
        for(int i = 0; i < c.size(); i++){
            if(sec[c[i]] == i){
                continue;
            }
            int l = i;
            int r = sec[c[i]];
            int gid = segt.query(l, r);
            if(gid == 1e9){
                gid = seg_g.size();
                seg_g.push_back({});
            }
            seg_g[gid].push_back(c[i]);
            seg_gid[c[i]] = gid;
            segt.modify(r, gid);
        }
        for(int i = 0; i < 2 * n; i++){
            segt.modify(i, 2);
        }
        vector<pair<int, int>> seg_lr(seg_g.size());
        for(int i = 0; i < seg_g.size(); i++){
            int l = 1e9;
            int r = -1;
            for(int j = 0; j < seg_g[i].size(); j++){
                int color = seg_g[i][j];
                l = min(l, fir[color]);
                r = max(r, sec[color]);
            }
            seg_lr[i] = {l, r};
        }
        vector<bool> v(seg_g.size(), false);
        int seg_l = c.size();
        vector<ll> seg(0);
        ll seg_cnt = 1;
        for(int i = c.size() - 1; i >= 0; i--){
            int gid = seg_gid[c[i]];
            if(v[gid]) {
                continue;
            }
            v[gid] = true;
            if(i < seg_l) {
                seg.push_back(seg_cnt);
                seg_cnt = seg_g[gid].size() * 2;
                for(int j = 0; j < seg_g[gid].size(); j++){
                    int color = seg_g[gid][j];
                    int l = fir[color];
                    int r = sec[color];
                    segt.modify(l, 1);
                    segt.modify(r, 1);
                    seg_l = min(seg_l, l);
                }
                continue;
            }
            int l = seg_lr[gid].first;
            int r = seg_lr[gid].second;
            if(segt.query(l, r) == 1){
                seg_cnt += seg_g[gid].size() * 2;
                seg_l = min(seg_l, l);
                for(int j = 0; j < seg_g[gid].size(); j++){
                    int color = seg_g[gid][j];
                    segt.modify(fir[color], 1);
                    segt.modify(sec[color], 1);
                }
            }
        }
        seg.push_back(seg_cnt);
        ll ans = 1;
        ll mod = 998244353;
        for(int i = 0; i < seg.size(); i++){
            ans = (ans * seg[i]) % mod;
        }
        cout << seg.size() - 1 << " " << ans << "\n";
    }
    
    return 0;
}
