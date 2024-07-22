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

//Codeforces - 1632D

//lets say that we have a non-boring array. How do we quickly determine if after appending an element, the array 
//becomes boring?

//first notice that any boring segment in this new array must end at the newly appended value. Since the GCD of a 
//segment monotonically decreases as the size increases, we can just binary search for when the size exceeds the
//GCD. To sample the GCD of a segment, we can do this in log(n)^2 time using segment tree. 

//If after appending a value, the array becomes boring, what can we do? We can just replace it with an arbitrarily large 
//prime number. This guarantees the GCD of a segment that includes this value is always 1. 

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

    Segtree() {}
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

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++){
            t[i + n] = arr[i];
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
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return gcd(a, b);};
    Segtree<int> segt(n, 0, 0, fmodify, fcombine);
    segt.assign(a);
    int ans = 0;
    int l = 0;
    for(int i = 0; i < n; i++){
        int low = l;
        int high = i;
        int ind = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(segt.query(mid, i + 1) >= i + 1 - mid) {
                ind = min(ind, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        if(segt.query(ind, i + 1) == i + 1 - ind) {
            ans ++;
            l = i + 1;
        }
        cout << ans << " \n"[i == n - 1];
    }
    
    return 0;
}