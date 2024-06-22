#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1549D

//given some subarray, how can we find an m such that all the values are congruent under that m

//first, we can notice that if x = y under m, then m | abs(x - y). Then, to find some m for a given subarray,
//we just need to take the gcd of the adjacent differences, and thats our m. Notice that if the gcd is 1, then
//an m doesn't exist. 

//finally, we can just apply 2 pointer technique to find the maximum length subarray where the gcd of the adjacent
//differences is not 1. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
        function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return gcd(a, b);};
        Segtree<ll> segt(n - 1, 0, 0, fmodify, fcombine); 
        for(int i = 0; i < n - 1; i++){
            segt.modify(i, abs(a[i] - a[i + 1]));
        }
        int ans = 1;
        int r = 0;
        for(int i = 0; i < n - 1; i++){
            if(segt.query(i) == 1){
                r = i + 1;
                continue;
            }
            while(r != n - 1 && segt.query(i, r) != 1){
                r ++;
            }
            int len = r - i + 1;
            if(segt.query(i, r) == 1){
                len --;
            }
            ans = max(ans, len);
        }
        cout << ans << "\n";
    }
    
    return 0;
}