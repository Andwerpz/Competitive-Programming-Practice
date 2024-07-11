#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1725L

//let's analyze what happens to the prefix sum of the array after we do an operation. 

//if we do the operation on index i, 
//pfx[i - 1] := pfx[i - 1] + a[i]
//pfx[i] := pfx[i] - a[i]
//pfx[i + 1] := pfx[i + 1]

//notice that by doing the operation on index i, we just swap pfx[i - 1] and pfx[i]. 

//in order for all the elements of a to be non-negative, pfx has to be arranged in non-decreasing
//order. Therefore, we just want to find the minimum number of swaps required to sort the pfx
//array. Minimum number of swaps required to sort an array is a classic problem, so just google it. 

//Also, in some cases it's impossible to make the entire array non-negative. If there is a negative
//value in pfx, or pfx[n - 1] is not the maximum value (since we cannot swap the last element), 
//then it's impossible to fix. 

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
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> pfx(n);
    pfx[0] = a[0];
    for(int i = 1; i < n; i++){
        pfx[i] = pfx[i - 1] + a[i];
    }
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        if(pfx[i] < 0){
            is_valid = false;
        }
    }
    //how many numbers before me are greater than me?
    ll ans = 0;
    vector<pair<ll, int>> ord(n);
    for(int i = 0; i < n; i++){
        ord[i].first = pfx[i];
        ord[i].second = i;
    }
    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    Segtree<int> segt(n, 0, 0, fmodify, fcombine); 
    int r = 0;
    for(int i = 0; i < n;){
        vector<int> tmp(0);
        while(r != n && ord[r].first == ord[i].first) {
            ans += (ll) segt.query(0, ord[r].second);
            tmp.push_back(ord[r].second);
            r ++;
        }
        for(int j = 0; j < tmp.size(); j++){
            segt.modify(tmp[j], 1);
        }
        i = r;
    }
    if(ord[0].first != pfx[n - 1]) {
        is_valid = false;
    }
    cout << (is_valid? ans : -1ll) << "\n";
    
    return 0;
}