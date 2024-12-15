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

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;
        function<T(T, T)> fmodify, fcombine;
        function<T(T, T, int)> fmodifyk;

        SegtreeLazy() {}
        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            uneut = updateNeutral, qneut = queryNeutral;
            this->fmodify = fmodify;
            this->fmodifyk = fmodifyk;
            this->fcombine = fcombine;
            n = 1; //raise n to nearest pow 2
            while(n < maxSize) n <<= 1;
            t = new T[n * 2], d = new T[n * 2];
            upd = new bool[n * 2];
            for(int i = 0; i < n; i++) t[i + n] = initVal;
            build();
        }
	
        //modifies the range [l, r)
        void modify(int l, int r, T val) {_modify(l, r, val, 0, n, 1);}
        void modify(int ind, T val) {modify(ind, ind + 1, val);}
        
        //queries the range [l, r)
        T query(int l, int r) {return _query(l, r, 0, n, 1);}
        T query(int ind) {return query(ind, ind + 1);}

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++) t[i + n] = arr[i];
            build();
        }
        void build() {
            for(int i = n - 1; i > 0; i--) t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            for(int i = 0; i < n * 2; i++){d[i] = uneut; upd[i] = false;}
        }

    private:
        void combine(int ind, int k) {
            if(ind >= n) return;
            int l = ind * 2, r = ind * 2 + 1;
            push(l, k / 2), push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }
        void push(int ind, int k) {
            if(!upd[ind]) return;
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2, r = ind * 2 + 1;
                apply(l, d[ind]), apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }
        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r) return;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) {apply(ind, val), push(ind, tr - tl); return;}
            int mid = tl + (tr - tl) / 2;
            if(l < mid) _modify(l, min(r, mid), val, tl, mid, ind * 2);
            if(r > mid) _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            combine(ind, tr - tl);
        }
        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r) return qneut;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) return t[ind];
            int mid = tl + (tr - tl) / 2;
            T lans = qneut, rans = qneut;
            if(l < mid) lans = _query(l, min(r, mid), tl, mid, ind * 2);
            if(r > mid) rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            return fcombine(lans, rans);
        }
};

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
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, pll>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].second.first >> a[i].second.second;
        }
        sort(a.begin(), a.end(), [](pair<int, pll> a, pair<int, pll> b) -> bool {
            if(a.second.first == b.second.first) return a.second.second < b.second.second;
            return a.second.first < b.second.first;
        });
        for(int i = 0; i < n; i++){
            a[i].first = i;
        }
        sort(a.begin(), a.end(), [](pair<int, pll> a, pair<int, pll> b) -> bool {
            if(a.second.second == b.second.second) return a.first > b.first;
            return a.second.second < b.second.second;
        });
        SegtreeLazy<ll> segt_min;   //increment modify, min query
        {
            function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
            function<ll(ll, ll, int)> fmodifyk = [](const ll src, const ll val, const int k) -> ll{return src + val;};
            function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return min(a, b);};
            segt_min = SegtreeLazy<ll>(n, 0, 5e18, 5e18, fmodify, fmodifyk, fcombine);
        }
        Segtree<ll> segt_sum;   //assignment modify, sum query
        {
            function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
            function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
            segt_sum = Segtree<ll>(n, 0, 0, fmodify, fcombine); 
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            int ind = a[i].first;
            ll s = a[i].second.first;
            ll t = a[i].second.second;
            // cout << "CONSIDER : " << ind << " " << s << " " << t << "\n";
            // cout << segt_sum.query(0, ind) << " " << segt_min.query(ind, n) << "\n";
            ll bsum = segt_sum.query(0, ind);
            if(bsum > s) continue;
            if(segt_min.query(ind, n) < t) continue;
            segt_sum.modify(ind, t);
            segt_min.modify(ind, n, -t);
            ll cmin = segt_min.query(ind);
            segt_min.modify(ind, (s - bsum) - cmin);
            ans ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}