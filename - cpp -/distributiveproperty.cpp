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

//Rutgers University Programming Contest Spring 2025 - D

//let's consider keeping track for each bit, 2^i, how many of them are on when we query x + t. 
//observe that the ith bit is on for some periodic contiguous range of t values, determined by the 
//first i bits of x. 

//Therefore, for each bit, we can probably just keep a segment tree of how many of that bit is on for each t 
//value, and then build the answer that way. 

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

const int B = 21;
vector<Segtree<int>> segt(B);

void qt1(int x) {
    for(int i = 0; i < B; i++){
        int mod = (1 << (i + 1));
        int cur = x & ((1 << (i + 1)) - 1);
        int l = (1 << i) - cur + (1 << (i + 2)), r = l + (1 << i);
        l %= (1 << (i + 1)), r %= (1 << (i + 1));
        segt[i].modify(r, 1);
    }
}

void qt2(int t) {
    int ans = 0;
    for(int i = 0; i < B; i++){
        int cur = t & ((1 << (i + 1)) - 1);
        int l = cur + 1, r = l + (1 << i);
        l %= (1 << (i + 1)), r %= (1 << (i + 1));
        int cnt = 0;
        if(l < r) cnt = segt[i].query(l, r);
        else cnt = segt[i].query(0, r) + segt[i].query(l, (1 << (i + 1)));
        if(cnt % 2) ans += (1 << i);
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < B; i++) {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        segt[i] = Segtree<int>((1 << (i + 1)), 0, 0, fmodify, fcombine); 
    }
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        qt1(x);
    }
    for(int i = 0; i < q; i++){
        int ty, v;
        cin >> ty >> v;
        if(ty == 1) qt1(v);
        else qt2(v);
    }
    
    return 0;
}