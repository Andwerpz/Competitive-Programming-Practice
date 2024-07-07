#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

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

void print_segt(SegtreeLazy<int> segt) {
    cout << "PRINT SEGT : \n";
    int inc = 1;
    for(int i = 1; i < segt.n * 2;){
        int j = i;
        i += inc;
        inc *= 2;
        while(j < i){
            cout << segt.t[j] << " ";
            j ++;
        }
        cout << "\n";
    }
    cout << "\n";

    inc = 1;
    for(int i = 1; i < segt.n * 2;){
        int j = i;
        i += inc;
        inc *= 2;
        while(j < i){
            cout << segt.d[j] << " ";
            j ++;
        }
        cout << "\n";
    }
    cout << "\n";
}

void modify(vector<int>& a, int l, int r, int val, SegtreeLazy<int> segt) {
    for(int i = l; i < r; i++){
        a[i] = segt.fmodify(a[i], val);
    }
}

int query(vector<int>& a, int l, int r, SegtreeLazy<int> segt) {
    int ans = segt.qneut;
    for(int i = l; i < r; i++){
        ans = segt.fcombine(ans, a[i]);
    }
    return ans;
}

bool test_segt(SegtreeLazy<int> segt, int valInit) {
    int n = segt.n;
    vector<int> arr(n, valInit);
    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % (n + 1);
        int val = rand() % 10;
        if(rand() % 2 == 1){
            val *= -1;
        }
        if(l > r){
            swap(l, r);
        }
        modify(arr, l, r, val, segt);
        cout << "MODIFY " << l << " " << r << " " << val << "\n";
        segt.modify(l, r, val);

        if(rand() % 10 == 0){
            int ind = rand() % n;
            int val = segt.query(ind, ind + 1);
            modify(arr, ind, ind + 1, -val, segt);
            segt.modify(ind, ind + 1, -val);
            cout << "MODIFY " << ind << " " << ind + 1 << " " << -val << "\n";
        }
    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " \n"[i == n - 1];
    }

    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % (n + 1);
        if(l > r){
            swap(l, r);
        }
        int arrans = query(arr, l, r, segt);
        int segtans = segt.query(l, r);
        cout << "QUERY " << l << " " << r << ", ARR : " << arrans << " SEGT : " << segtans << "\n";
        if(arrans != segtans) {
            print_segt(segt);
            return false;
        }
    }
    cout << "\n";
    return true;
}

void run_segt_tests(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
    srand(time(0));
    bool isValid = true;
    for(int i = 0; i < 100; i++){
        SegtreeLazy<int> segt(maxSize, updateNeutral, queryNeutral, updateNeutral, fmodify, fmodifyk, fcombine);
        if(!test_segt(segt, updateNeutral)) {
            cout << "TEST FAILED\n";
            return;
        }
    }
    cout << "TEST PASSED\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n = 100;

    // -- ASSIGNMENT MODIFY, SUM QUERY --
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val * k;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        run_segt_tests(n, 0, 0, fmodify, fmodifyk, fcombine);
    }

    // -- INCREMENT MODIFY, MINIMUM QUERY --
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        run_segt_tests(n, 0, 1e9, fmodify, fmodifyk, fcombine);
    }

    // -- ASSIGNMENT MODIFY, MINIMUM QUERY --
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        run_segt_tests(n, 0, 1e9, fmodify, fmodifyk, fcombine);
    }

    // -- 01 ASSIGNMENT MODIFY, FIRST LAST INDEX 01 QUERY -- 
    // when querying, returns a struct that tells you the first and last indices of 0 and 1
    // in the range that you queried. 
    {
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
        SegtreeLazy<seg> segt(n, {0}, {0}, {1, false}, fmodify, fmodifyk, fcombine);
        //example use
        segt.modify(0, {0, false}); //set range to 0
        segt.modify(1, 5, {0, true});   //set range to 1
        seg a = segt.query(5, 10);  //get attr over range
    }

    // -- INCREMENT MODIFY, MINIMUM AND MINIMUM INDEX QUERY --
    //if there are multiple indices with the minimum value, will return the minimum index out of all of them. 
    {
        struct seg {
            int mn, ind;
            seg() {
                mn = 1e9;
                ind = 0;
            }
            seg(int _mn, int _ind) {
                mn = _mn;
                ind = _ind;
            }
            seg(int val) {
                mn = val;
            }
        };
        function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
            return seg(src.mn + val.mn, src.ind);
        };
        function<seg(seg, seg, int)> fmodifyk = [](const seg src, const seg val, const int k) -> seg{
            return seg(src.mn + val.mn, src.ind);
        };
        function<seg(seg, seg)> fcombine = [](const seg a, const seg b) -> seg{
            if(a.mn == b.mn) {
                return seg(a.mn, min(a.ind, b.ind));
            }
            return a.mn < b.mn? seg(a.mn, a.ind) : seg(b.mn, b.ind);
        };
        SegtreeLazy<seg> segt(n + 1, seg(0), seg(), seg(), fmodify, fmodifyk, fcombine);
        vector<seg> init_arr(n + 1);
        for(int i = 0; i <= n; i++){
            init_arr[i] = seg(0, i);
        }
        segt.assign(init_arr);
    }

    // -- ADD OR MULTIPLY MODIFY, SUM UNDER MOD QUERY --
    {   
        //modify {a, b} means multiply by b, then add a. 
        ll mod = 1e9 + 7;
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
    }

    return 0;
}


