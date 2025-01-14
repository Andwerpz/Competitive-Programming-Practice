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

//AtCoder - AGC19C

//Notice that while cutting a corner around a fountain does save around 5 meters, going out of your way 
//to try to cut corners is never going to be worth it, as you have to cut around 20 corners to save
//moving 1 segment. So an optimal path is always going to be moving between (x1, y1) to (x2, y2) as directly
//as possible, while also trying to cut as many corners as possible. 

//WLOG, we can assume that x1 <= x2, and y1 <= y2. Then to determine the maximum amount of fountains we 
//can visit, we can just do some dp, accelerated with a segment tree and coordinate compression. There is
//one edge case we have to be wary of, and that is when we're forced to go around a fountain. This only 
//happens iff it's possible to visit min(x2 - x1, y2 - y1) + 1 fountains, in which case it's optimal
//to cut as many corners, and also go around the fountain rather than taking a detour. 

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

const ld PI = acos(-1);
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    if(x1 > x2) {
        x1 *= -1, x2 *= -1;
        for(pii& x : a) x.first *= -1;
    }
    if(y1 > y2) {
        y1 *= -1, y2 *= -1;
        for(pii& x : a) x.second *= -1;
    }
    {
        vector<pii> tmp;
        for(pii x : a) if(x.first >= x1 && x.first <= x2 && x.second >= y1 && x.second <= y2) tmp.push_back(x);
        a = tmp;
    }
    sort(a.begin(), a.end(), [](pii a, pii b) -> bool {
        return a.second < b.second;
    });
    for(int i = 0; i < a.size(); i++){
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
    Segtree<int> segt(a.size() + 1, 0, -1e9, fmodify, fcombine); 
    segt.modify(a.size(), 0);
    for(int i = a.size() - 1; i >= 0; i--){
        int y = a[i].second;
        int val = segt.query(y + 1, a.size() + 1) + 1;
        segt.modify(y, val);
    }
    int amt = segt.query(0, a.size() + 1);
    ld ans = (x2 - x1) * 100.0 + (y2 - y1) * 100.0;
    if(amt == min(x2 - x1, y2 - y1) + 1) {
        //forced to go around fountain
        ans -= amt * 20.0;
        ans += (2.0 * PI * 10) / 4.0 * (amt + 1);
    }
    else {
        ans -= amt * 20.0;
        ans += (2.0 * PI * 10) / 4.0 * amt;
    }
    cout << fixed << setprecision(15) << ans << "\n";
    
    return 0;
}