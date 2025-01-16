#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//AtCoder - ARC189D

//Instead of having to be strictly greater, let's first solve if you can absorb if you're also equal. Then, we'll account
//for the change at the end. 

//Notice that the maximum element can always absorb everything. Then, we can partition the array into two parts, to the
//left and right of the maximum element. The maximum in these segments can absorb anything in these segments, and if they
//can pass the 'barrier' that is the array maximum, then they can also absorb anything. This motivates a divide and 
//conquer solution. 

//To find the indices of maximum elements, we can use a range max query segment tree. Since our soln should query at most 
//twice per maximum element, this should run in O(n * log(n))

//to account for our initial change where we allowed equal elements to absorb each other, we'll go through our computed
//answer, and set ans[i] = a[i] if a[i] is not greater than any of its adjacent elements. If a[i] is greater than one, then 
//it is able to absorb any equal element since it gets this little initial boost, but if it's not greater then you can't do
//anything. 

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

Segtree<pii> segt;
vl ans, pfx;
void solve(int l, int r, ll above, ll thresh) {
    if(l == r) return;
    ll csum = pfx[r] - pfx[l];
    vi mxind;
    int mx = segt.query(l, r)[0];
    int ptr = l;
    while(true) {
        pii res = segt.query(ptr, r);
        if(res[0] != mx) break;
        mxind.push_back(res[1]);
        ptr = res[1] + 1;
    }
    for(int x : mxind) ans[x] = csum > thresh? above : csum;
    mxind.push_back(r);
    ll nabove = csum > thresh? above : csum;
    solve(l, mxind[0], nabove, mx);
    for(int i = 0; i < mxind.size() - 1; i++) {
        solve(mxind[i] + 1, mxind[i + 1], nabove, mx);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{return val;};
    function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{return a[0] == b[0]? (a[1] < b[1]? a : b) : (a[0] > b[0]? a : b);};
    segt = Segtree<pii>(n, {0, 0}, {(int) -1e9, -1}, fmodify, fcombine);
    vector<pii> tmp(n);
    for(int i = 0; i < n; i++) tmp[i] = {(int) a[i], i};
    segt.assign(tmp);
    pfx = vl(n + 1, 0), ans = vl(n, -1);
    for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + a[i - 1];
    solve(0, n, 0, 1e18);
    for(int i = 0; i < n; i++){
        if(i != 0 && a[i] > a[i - 1]) continue;
        if(i != n - 1 && a[i] > a[i + 1]) continue;
        ans[i] = a[i];
    }
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}