#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1886D

//let's try to simulate the process in reverse:
//initially, we start out with a full set from 1 to n, and in the reverse order of the given string, 
//we either remove the maximum element, remove the minimum element, or remove some middle element. 
//we can see that we will always have 1 choice when removing max or min, and when removing the middle element, 
//the number of choices is exactly equal to the number of remaining elements - 2.

//Importantly, the number of choices when removing the middle element isn't affected by what elements you have
//previously removed from the set, only the amount of elements remaining matters. 

//from here, we can just take the product of all the choices for each step, and that's the answer for a given
//string. To quickly answer the queries, we can use a single modify, range product query segment tree. 

ll mod = 998244353;

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

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    //assignment modify, product query
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return (a * b) % mod;};
    Segtree<ll> segt(n, 0, 1, fmodify, fcombine); 
    string s;
    cin >> s;
    s = "?" + s;
    segt.modify(0, 1);
    for(int i = 1; i < n; i++){
        if(s[i] == '?') {
            segt.modify(i, i - 1);
        }
        else {
            segt.modify(i, 1);
        }
    }
    cout << segt.query(0, n) << "\n";
    for(int i = 0; i < m; i++){
        int ind;
        char c;
        cin >> ind >> c;
        s[ind] = c;
        if(c == '?') {
            segt.modify(ind, ind - 1);
        }
        else {
            segt.modify(ind, 1);
        }
        cout << segt.query(0, n) << "\n";
    }
    
    return 0;
}
