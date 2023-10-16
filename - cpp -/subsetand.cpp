#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023 Columbia University Local Contest F

//we only want to include a number into the bitwise AND sum if it includes k. 

//use a segment tree to do the bitwise AND range sum. 

//single modify, range query
template <typename T>
struct Segtree {
    //note that t[0] is not used
    T n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(T n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < 2 * n; i++){
            t[i] = uneut;
        }
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
        T res = qneut;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                res = fcombine(res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res = fcombine(res, t[r]);
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, q;
    cin >> n >> k >> q;
    function<ll(ll, ll)> fmodify = [](const int src, const int val) -> int{return val;};
    function<ll(ll, ll)> fcombine = [](const int a, const int b) -> int{return a & b;};
    Segtree<ll> segt(n, (1ll << 31) - 1, (1ll << 31) - 1, fmodify, fcombine); 
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if((next & k) == k) {
            segt.modify(i, next);
        }
    }
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l --;
        bool valid = k == segt.query(l, r);
        cout << (valid? "YES" : "NO") << "\n";
    }

    return 0;
}
