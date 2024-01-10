#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1705E

//nice lazy segment tree modification problem. Finally solved after almost 2 years :D

//we can think of each number x as contributing bit 2^x to a big number. Then, the maximum possible
//number the professor can write is just going to be the most significant bit if we sum all the
//values on the board. 

//we can keep track of the final bits in the big number using a boolean array. Then, we can try to
//figure out how to efficiently add and subtract a single bit from the number. 

//when we add a bit at index i, we need to look for the first zero after i, denote this index as
//index j. Then, we set the bit at index j to 1, and set all bits in the range [i, j) to 0. 
//likewise, when we subtract, we look for the first 1, set it to 0, and set the stuff before to 1. 

//these both can be done using a lazy segment tree. We can keep track of the closest 1 and 0 to the
//left in each range, and the size of each range. To find the maximum number, we simply have to
//find the rightmost 1. We can simply keep track of the closest 1 to the right in each range. 

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

struct seg {
    int size;
    bool has_one, has_zero;
    int pfx_one, sfx_one;   //distance from beginning and end of closest 1
    int pfx_zero, sfx_zero; 
    seg(int size, bool which) { //sets the entire segment the same value
        this->size = size;
        has_one = which;
        has_zero = !which;
        pfx_one = 0;
        sfx_one = 1;
        pfx_zero = 0;
        sfx_zero = 1;
    }
    seg(int size){
        this->size = size;
        has_one = false;
        has_zero = false;
    }
    seg() {}
};

void add(SegtreeLazy<seg>& segt, int ind) {
    //find first 0 after ind, replace 0 with 1 and replace all ones before with 0s
    seg a = segt.query(ind, segt.n);
    int f_zero = ind + a.pfx_zero;
    segt.modify(f_zero, {0, true});
    segt.modify(ind, f_zero, {0, false});
}

void sub(SegtreeLazy<seg>& segt, int ind) {
    //find first one after ind, replace 1 with 0 and replace all zeroes before with 1s
    seg a = segt.query(ind, segt.n);
    int f_one = ind + a.pfx_one;
    segt.modify(f_one, {0, false});
    segt.modify(ind, f_one, {0, true});
}

int maxInd(SegtreeLazy<seg>& segt) {
    seg a = segt.query(0, segt.n);
    return segt.n - a.sfx_one;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    //assignment modify, range 'seg' query. 
    function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
        //set this element to 0 or 1
        seg next(src.size, val.has_one);
        return next;
    };
    function<seg(seg, seg, int)> fmodifyk = [](const seg src, const seg val, const int k) -> seg{
        //set the entire range to 0 or 1
        seg next(src.size, val.has_one);
        return next;
    };
    function<seg(seg, seg)> fcombine = [](const seg lhs, const seg rhs) -> seg{
        //combines lhs and rhs into one segment
        seg next(lhs.size + rhs.size, false);
        next.has_one = lhs.has_one || rhs.has_one;
        next.has_zero = lhs.has_zero || rhs.has_zero;
        if(next.has_one) {
            next.pfx_one = lhs.has_one? lhs.pfx_one : lhs.size + rhs.pfx_one;
            next.sfx_one = rhs.has_one? rhs.sfx_one : rhs.size + lhs.sfx_one;
        }
        if(next.has_zero) {
            next.pfx_zero = lhs.has_zero? lhs.pfx_zero : lhs.size + rhs.pfx_zero;
            next.sfx_zero = rhs.has_zero? rhs.sfx_zero : rhs.size + lhs.sfx_zero;
        }
        return next;
    };
    SegtreeLazy<seg> segt(2e5 + 100, {0}, {0}, {1, false}, fmodify, fmodifyk, fcombine);
    segt.modify(0, 1, {0, true});
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        add(segt, a[i]);
    }
    for(int i = 0; i < q; i++){
        int k, l;
        cin >> k >> l;
        k --;
        sub(segt, a[k]);
        add(segt, l);
        a[k] = l;
        cout << maxInd(segt) << "\n";
    }
    
    return 0;
}
