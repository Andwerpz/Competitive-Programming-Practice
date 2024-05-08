#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//AtCoder - ABC346G

//for each left bound, consider the number of right bounds that will make a valid segment. 
//we can examine each unique number individually. Notice that each value will make a 'good' segment of
//right bounds, specifically between the first and second occurence of that value to the right
//of the left bound we're looking at. 

//then, for a given left bound, we want to consider all values. The amount of right bounds is simply the length
//of the union of the 'good' segments given by each value. 

//to quickly compute the length of union of segments online, we can use a lazy segment tree. 

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
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] --;
    }
    struct seg {
        int min_val, nr_min;
        seg() {
            min_val = 0;
            nr_min = 0;
        }
        seg(int _min_val, int _nr_min) {
            min_val = _min_val;
            nr_min = _nr_min;
        }
        seg(int _min_val) {
            min_val = _min_val;
            nr_min = 0;
        }
    };
    function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
        return {src.min_val + val.min_val, src.nr_min};
    };
    function<seg(seg, seg, int)> fmodifyk = [](const seg src, const seg val, const int k) -> seg{
        return {src.min_val + val.min_val, src.nr_min};
    };
    function<seg(seg, seg)> fcombine = [](const seg a, const seg b) -> seg{
        seg ret = {min(a.min_val, b.min_val), 0};
        if(a.min_val == ret.min_val) {
            ret.nr_min += a.nr_min;
        }
        if(b.min_val == ret.min_val) {
            ret.nr_min += b.nr_min;
        }
        return ret;
    };
    SegtreeLazy<seg> segt(n, {}, {}, {0, 1}, fmodify, fmodifyk, fcombine);
    //for each element, keep track of it's next occurrence
    vector<int> next(n + 1, n);
    {
        vector<int> ls(n, -1);
        for(int i = n - 1; i >= 0; i--){
            int cur = a[i];
            if(ls[cur] != -1){
                next[i] = ls[cur];
            }
            ls[cur] = i;
        }
    }
    ll ans = 0;
    //populate initial stuff
    {
        set<int> v;
        for(int i = 0; i < n; i++){
            if(v.count(a[i])) {
                continue;
            }
            v.insert(a[i]);
            segt.modify(i, next[i], {1});
        }
    }
    //compute ans
    for(int i = 0; i < n; i++){
        seg cur = segt.query(i, n);
        ans += n - i - (cur.min_val == 0) * cur.nr_min;
        int s0 = i;
        int s1 = next[i];
        int s2 = next[s1];
        segt.modify(s0, s1, {-1});
        segt.modify(s1, s2, {1});
    }
    cout << ans << "\n";
    
    return 0;
}
