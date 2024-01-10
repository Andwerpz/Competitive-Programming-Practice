#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//single modify, range query
template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
        }
        build();
    }

    void build() { // build the tree after manually assigning the values.
        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none) {
            return r_res;
        }
        if(r_none) {
            return l_res;
        }
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

void modify(vector<int>& a, int ind, int val, Segtree<int> segt) {
    a[ind] = segt.fmodify(a[ind], val);
}

int query(vector<int>& a, int l, int r, Segtree<int> segt) {
    int ans = segt.qneut;
    for(int i = l; i < r; i++){
        ans = segt.fcombine(ans, a[i]);
    }
    return ans;
}

bool test_segt(Segtree<int> segt, int valInit) {
    int n = segt.n;
    vector<int> arr(n, valInit);
    for(int i = 0; i < n; i++){
        int ind = rand() % n;
        int val = rand() % 10;
        modify(arr, ind, val, segt);
        cout << "MODIFY " << ind << " " << val << "\n";
        segt.modify(ind, val);
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
            return false;
        }
    }
    cout << "\n";
    return true;
}

void run_segt_tests(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int)> fcombine) {
    srand(time(0));
    bool isValid = true;
    for(int i = 0; i < 100; i++){
        Segtree<int> segt(maxSize, updateNeutral, queryNeutral, fmodify, fcombine);
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

    // -- INCREMENT MODIFY, SUM QUERY -- 
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        run_segt_tests(n, 0, 0, fmodify, fcombine); 
    }

    // -- ASSIGNMENT MODIFY, MIN QUERY -- 
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        run_segt_tests(n, 0, 1e9, fmodify, fcombine); 
    }

    // -- INCREMENT MODIFY, MAX SUBARRAY SUM QUERY --
    //subarray has to contain at least 1 element. 
    {   
        struct seg {
            ll max_pfx, max_sfx, max_sum, sum;
            seg() {};
            seg(ll sum) {
                this->sum = sum;
            }
            seg(ll max_pfx, ll max_sfx, ll max_sum, ll sum) {
                this->max_pfx = max_pfx;
                this->max_sfx = max_sfx;
                this->max_sum = max_sum;
                this->sum = sum;
            }
        };
        function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
            seg next;
            next.max_pfx = src.max_pfx + val.sum;
            next.max_sfx = src.max_sfx + val.sum;
            next.max_sum = src.max_sum + val.sum;
            next.sum = src.sum + val.sum;
            return next;
        };
        function<seg(seg, seg)> fcombine = [](const seg lhs, const seg rhs) -> seg{
            seg next;
            next.max_pfx = max(lhs.max_pfx, lhs.sum + rhs.max_pfx);
            next.max_sfx = max(rhs.max_sfx, rhs.sum + lhs.max_sfx);
            next.max_sum = max({lhs.max_sum, rhs.max_sum, lhs.max_sfx + rhs.max_pfx});
            next.sum = lhs.sum + rhs.sum;
            return next;
        };
        Segtree<seg> segt(n, {0, 0, 0, 0}, {0, 0, 0, 0}, fmodify, fcombine);
    }
    
    // -- ASSIGNMENT MODIFY, XOR BASIS QUERY --
    //returns the xor basis of a range. Refer to https://codeforces.com/blog/entry/68953
    {   
        struct seg{
            int basis[20];
            int nr_b = 0;
            seg(int val) {
                fill(basis, basis + 20, -1);
                nr_b += basisAdd(val);
            }
            seg() {
                fill(basis, basis + 20, -1);
            }
            bool basisAdd(int val, int start = 0) {
                for(int i = start; i < 20; i++){
                    if((val & 1 << i) == 0){
                        continue;
                    }
                    if(basis[i] == -1){
                        basis[i] = val;
                        return true;
                    }
                    val ^= basis[i];
                }
                return false;
            }
        };
        function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
            return val;
        };
        function<seg(seg, seg)> fcombine = [](const seg a, const seg b) -> seg{
            if(a.nr_b == 20){
                return a;
            }
            if(b.nr_b == 20){
                return b;
            }
            seg next;
            for(int i = 0; i < 20; i++){
                next.basis[i] = a.basis[i];
            }
            next.nr_b = a.nr_b;
            for(int i = 19; i >= 0; i--){
                if(b.basis[i] != -1){
                    next.basisAdd(b.basis[i], i);
                }
            }
            return next;
        };
        Segtree<seg> segt(n, {}, {}, fmodify, fcombine);
    }

    return 0;
}
