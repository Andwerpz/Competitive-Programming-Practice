#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1917D

//this solution gets WA

//single modify, range query
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
    
    ll mod = 998244353;
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<ll> p(n), q(k);
        for(int i = 0; i < n; i++){
            cin >> p[i];
        }
        for(int i = 0; i < k; i++){
            cin >> q[i];
        }
        ll ans = 0;
        ll q_inv = 0;
        //find number of inversions in q
        {   
            //single increment modify, range sum query
            function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
            function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
            Segtree<ll> segt(k, 0, 0, fmodify, fcombine); 
            for(int i = k - 1; i >= 0; i--){
                q_inv += segt.query(0, i);
                segt.modify(q[i], 1);
            }
        }
        cout << "QINV : " << q_inv << "\n";
        ans += (q_inv * n) % mod;
        //from here, assume q is sorted; q[i] = i.
        //single increment modify, range sum query
        function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
        function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
        Segtree<ll> segt(n, 0, 0, fmodify, fcombine); 
        int nr_v = 0;
        vector<bool> v(n, false);
        priority_queue<pair<ll, pair<int, int>>> qu;    //{-val, {p ind, pow2}}
        for(int i = 0; i < n; i++){
            qu.push({-p[i], {i, 0}});
        }
        while(qu.size() != 0 && nr_v != n) {
            int cur = qu.top().second.first;
            int pow_2 = qu.top().second.second;
            ll cur_val = -qu.top().first;
            qu.pop();
            cout << "CUR : " << cur << " " << cur_val << " " << pow_2 << "\n";
            if(!v[cur]) {
                nr_v ++;
                v[cur] = true;
                ll nr_inv = segt.query(cur, n);
                nr_inv %= mod;
                cout << "COUNT INV : " << cur << " " << nr_inv << "\n";
                ans = (ans + nr_inv) % mod;
                segt.modify(cur, (k * (k + 1) / 2ll) % mod);
            }
            else {
                segt.modify(cur, k - pow_2);
            }
            if(pow_2 + 1 < k) {
                qu.push({-(cur_val * 2), {cur, pow_2 + 1}});
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
