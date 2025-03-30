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

//3rd Universal Cup, Stage 13 Sendai - H

//We can greedily maximize the first element, then the second element, and so on. 

//to maximize the first element, observe that we're restricted to picking some element with index of form a[xk], where
//x is some non-negative integer. The second character is restricted to a[xk + 1], and has to be after the first, 
//and so on. We can quickly find the maximum element with lowest index by just making k segment trees, one
//corresponding to each remainder. 

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
    
    int n, k;
    cin >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    //max val and min index query
    function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{return val;};
    function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{
        return a.first == b.first? (a.second < b.second? a : b) : (a.first > b.first? a : b);
    };
    vector<Segtree<pii>> segt(k);
    {
        vector<vector<pii>> tmp(k);
        for(int i = 0; i < n; i++) tmp[i % k].push_back({a[i], i});
        for(int i = 0; i < k; i++) {
            segt[i] = Segtree<pii>(tmp[i].size(), {0, 0}, {-1e9, -1}, fmodify, fcombine);
            segt[i].assign(tmp[i]);
        }
    }
    vi ans(0);
    int ptr = 0;
    while(ptr != n){
        int rem = ptr % k;
        int sind = ptr / k;
        pii ret = segt[rem].query(sind, segt[rem].n);
        ans.push_back(ret.first);
        ptr = ret.second + 1;
    }
    for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}