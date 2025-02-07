#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Kattis - megainversions

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
    Segtree<ll> segt(n, 0, 0, fmodify, fcombine);
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<pii> ord(n);
    for(int i = 0; i < n; i++) ord[i] = {a[i], i};
    sort(ord.begin(), ord.end(), [](pii a, pii b) -> bool {
        return a.first != b.first? a.first > b.first : a.second > b.second;
    });
    vl lt1(n, -1);
    for(int i = 0; i < n; i++){
        int ind = ord[i].second;
        lt1[ind] = segt.query(0, ind);
        segt.modify(ind, 1);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) segt.modify(i, 0);
    for(int i = 0; i < n; i++){
        int ind = ord[i].second;
        ans += segt.query(0, ind);
        segt.modify(ind, lt1[ind]);
    }
    cout << ans << "\n";
    
    return 0;
}