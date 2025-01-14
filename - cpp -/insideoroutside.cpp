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
    
    int n, m;
    cin >> n >> m;
    vector<pii> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][0] --;
    }   
    vi ans(m, 0);
    bool oneop = false;
    for(int i = 0; i < m; i++){
        if(a[i][0] == 0 && a[i][1] == n) {
            oneop = true;
            ans[i] = 1;
            break;
        }
    }
    if(oneop) {
        cout << "1\n";
        for(int i = 0; i < m; i++) cout << ans[i] << " ";
        cout << "\n";
        return 0;
    }
    function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{return val;};
    function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{return a[0] < b[0]? a : b;};
    Segtree<pii> segt(n, {0, 0}, {(int) 1e9, -1}, fmodify, fcombine);
    vector<pii> minr(n, {(int) 1e9, -1});
    for(int i = 0; i < m; i++){
        if(a[i][1] < minr[a[i][0]][0]) minr[a[i][0]][0] = a[i][1], minr[a[i][0]][1] = i;
    }
    segt.assign(minr);
    bool found = false;
    int op_amt = -1;
    if(!found) {
        for(int i = 0; i < m; i++){
            int l = a[i][0], r = a[i][1];
            //check if this segment is disjoint with another
            pii ql = segt.query(0, l), qm = segt.query(l + 1, r), qr = segt.query(r, n);
            if(ql[1] != -1 && ql[0] <= l) {
                found = true, ans[i] = 2, ans[ql[1]] = 2, op_amt = 2;
                break;
            } 
            if(qr[1] != -1) {
                found = true, ans[i] = 2, ans[qr[1]] = 2, op_amt = 2;
                break;
            }
            //check if this segment completely contains another
            if(qm[1] != -1 && qm[0] <= r) {
                found = true, ans[i] = 1, ans[qm[1]] = 2, op_amt = 2;
                break;
            }
            // cout << "MINR : " << minr[l][1] << " " << minr[l][0] << "\n";
            if(minr[l][1] != -1 && minr[l][1] != i) {
                found = true, ans[i] = 1, ans[minr[l][i]] = 2, op_amt = 2;
                break;
            }
        }
    }
    //otherwise, all segments must be partially intersecting with every other segment. 
    //If there are two segments which when unioned contain the entire thing, can just pick those two
    if(!found) {
        int lind = -1, rind = -1;
        for(int i = 0; i < m; i++){
            if(a[i][0] == 0) lind = i;
            if(a[i][1] == n) rind = i;
        }
        if(lind != -1 && rind != -1) found = true, ans[lind] = 1, ans[rind] = 1, op_amt = 2;
    }
    //If there are 3 or more segments, then we can just choose any 3 of them and it works.
    if(!found) {
        if(m >= 3) {
            int x = 0, y = 1, z = 2;
            if(a[x][0] > a[y][0]) swap(x, y);
            if(a[x][0] > a[z][0]) swap(x, z);
            if(a[y][0] > a[z][0]) swap(y, z);
            found = true, ans[x] = 1, ans[y] = 2, ans[z] = 1, op_amt = 3;
        }
    } 
    if(!found) {
        cout << "-1\n";
        return 0;
    }
    cout << op_amt << "\n";
    for(int i = 0; i < m; i++) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}