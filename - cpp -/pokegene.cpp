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

//NCNA 2018 Regional A

//first, sort all strings in ascending lexicographical order. 
//next, observe that all children of a string will be contained within a contiguous subarray once we've
//sorted the strings. 

//we can do a divide and conquer solution. For some segment [l, r), if we have more than L children, we need
//to recurse downwards. If we have less than L children, return 0. Otherwise, we compute how many valid parents
//there are of these L children. This can be done with some LCP. 

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

Segtree<int> zsegt;
ll solve(vector<pair<string, int>>& a, vi& b, vi& z, int l, int r, int y, int depth) {
    while(r - l > 0 && a[b[l]].first.size() < depth) l ++;
    while(r - l > 0 && a[b[r - 1]].first.size() < depth) r --;
    int cnt = 0;
    for(int i = l; i < r; i++) {
        if(a[b[i]].first.size() < depth) continue;
        cnt ++;
    }
    if(cnt < y) return 0;
    else if(cnt == y) {
        int lcp = 1e9;
        int prev = -1;
        int mnlen = 0;
        for(int i = l; i < r; i++) {
            if(a[b[i]].first.size() < depth) continue;
            mnlen = min(mnlen, (int) a[b[i]].first.size());
            if(prev == -1) {
                lcp = a[b[i]].first.size();
            }
            else {
                lcp = min(lcp, zsegt.query(prev, b[i]));
            }
            prev = b[i];
        }
        assert(lcp >= depth);
        ll ans = lcp - depth + 1;
        if(depth == 0) ans = max(ans - 1, 0ll);   //empty string isn't valid
        return ans;
    }

    ll ans = 0;
    int tot_lcp = zsegt.query(b[l], b[r - 1]);
    assert(tot_lcp >= depth);
    for(int i = l; i < r;) {
        if(a[b[i]].first.size() <= tot_lcp) {
            i ++;
        }
        int cr = i;
        while(cr != r && (a[b[cr]].first.size() <= tot_lcp || a[b[cr]].first[tot_lcp] == a[b[i]].first[tot_lcp])) cr ++;
        ans += solve(a, b, z, i, cr, y, tot_lcp + 1);
        i = cr;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<pair<string, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    vi indmp(n);
    for(int i = 0; i < n; i++) {
        indmp[a[i].second] = i;
    }
    vi z(n, 0);    //lcp with next element
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < min(a[i].first.size(), a[i + 1].first.size()); j++) {
            if(a[i].first[j] != a[i + 1].first[j]) break;
            z[i] ++;
        }
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    zsegt = Segtree<int>(n, 0, 1e9, fmodify, fcombine); 
    for(int i = 0; i < n; i++) {
        zsegt.modify(i, z[i]);
    }
    while(q--) {
        int x, y;
        cin >> x >> y;
        vi b(x);
        for(int i = 0; i < x; i++) {
            cin >> b[i];
            b[i] = indmp[b[i] - 1];
        }
        sort(b.begin(), b.end());
        ll ans = solve(a, b, z, 0, x, y, 0);
        cout << ans << "\n";
    }
    
    return 0;
}