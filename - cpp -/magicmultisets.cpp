#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 981G

//for each element x, we can maintain a set of segments that store which sets contain x. Whenever we add x on 
//a segment, we can update this set of segments for x in amortized O(log(n)) time. 

//next, how do we keep track of multiset sizes? If we add x to a segment that already contains it, then we multiply the
//size by 2, and if we add to a segment that doesn't contain it, we add 1. Thus, we need a segment tree that can
//support range multiplication and addition. We can actually do that pretty easily. 

//The editorial includes a way to not have to do the nasty implementation associated with maintaining the set of segments. 

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n; i++){
                t[i + n] = initVal;
            }
            build();
        }

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++){
                t[i + n] = arr[i];
            }
            build();
        }

        //build tree after manually assigning values
        void build() {
            for(int i = n - 1; i > 0; i--){
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
            return _query(ind, ind + 1, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, int k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            int mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            int mid = tl + (tr - tl) / 2;
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    map<int, set<pii>> m;   //0 = begin, 1 = end
    ll mod = 998244353;
    function<pll(pll, pll)> fmodify = [&mod](const pll src, const pll val) -> pll{
        return {(src.first * val.second + val.first) % mod, (src.second * val.second) % mod};
    };
    function<pll(pll, pll, int)> fmodifyk = [&mod](const pll src, const pll val, const int k) -> pll{
        return {(src.first * val.second + val.first * k) % mod, (src.second * val.second) % mod};
    };
    function<pll(pll, pll)> fcombine = [&mod](const pll a, const pll b) -> pll{
        return {(a.first + b.first) % mod, (a.second * b.second) % mod};
    };
    SegtreeLazy<pll> segt(n, {0, 1}, {0, 0}, {0, 0}, fmodify, fmodifyk, fcombine);
    for(int i = 0; i < q; i++){
        int t, l, r;
        cin >> t >> l >> r;
        l --;
        if(t == 1){
            int x;
            cin >> x;
            int ptr = l;
            while(ptr < r) {
                auto sptr = m[x].lower_bound({ptr, -1});
                int nr = r;
                int btype = 0;
                if(sptr != m[x].end()) {
                    nr = min(nr, sptr->first);
                    btype = sptr->second;
                }
                if(btype == 0){
                    //starting a segment, add 1
                    segt.modify(ptr, nr, {1, 1});
                }
                else {
                    //ending a segment, mult 2
                    segt.modify(ptr, nr, {0, 2});
                }
                if(m[x].count({nr, btype})) {
                    m[x].erase({nr, btype});
                }
                ptr = nr;
            }
            {
                m[x].insert({l, 0});
                auto sptr = m[x].find({l, 0});
                if(sptr != m[x].begin()) {
                    sptr --;
                    if(sptr->second == 0){
                        sptr ++;
                        m[x].erase(sptr);
                    }
                }
            }
            {
                m[x].insert({r, 1});
                auto sptr = m[x].find({r, 1});
                sptr ++;
                if(sptr != m[x].end() && sptr->second == 1){
                    sptr --;
                    m[x].erase(sptr);
                }
            }
        }
        else {
            cout << segt.query(l, r).first << "\n";
        }
    }
    
    return 0;
}