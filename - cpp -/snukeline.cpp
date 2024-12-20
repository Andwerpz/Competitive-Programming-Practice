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

//AtCoder - ARC68E

//My initial thought is that since M is small, we can have an array of size M + 1 representing the
//train stops, and for every segment L_i -> R_i, we add one to the entire segment. Then, for each
//i from 1 to M, we can just go through and add up the value from all the stops. 

//However, this will return the incorrect answer due to some segments counting twice. The key 
//observation here is that for some i, the segments that will count twice are the segments with
//size >= i, and the segments with size >= i are guaranteed to be visited by train i. 

//So we can iterate i from 1 to M, and if there was only some way to dynamically update our 
//train stop array. Well, there is, and it's called a lazy segment tree. So for every i, we'll
//just add in all segments of length i - 1 to our segment tree, and then query. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        a[i].second ++;
    }
    sort(a.begin(), a.end(), [](pii a, pii b) -> bool {
        return (a.second - a.first) < (b.second - b.first);
    });
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll, int)> fmodifyk = [](const ll src, const ll val, const int k) -> ll{return src + val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return min(a, b);};
    SegtreeLazy<ll> segt(m + 1, 0, 1e18, 0, fmodify, fmodifyk, fcombine);
    vi ans(m + 1, 0);
    int ptr = 0;
    for(int i = 1; i <= m; i++){
        while(ptr != n && a[ptr].second - a[ptr].first < i) {
            segt.modify(a[ptr].first, a[ptr].second, 1);
            ptr ++;
        }
        ans[i] = n - ptr;
        for(int j = i; j <= m; j += i){
            ans[i] += segt.query(j);
        }
    }
    for(int i = 1; i <= m; i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}