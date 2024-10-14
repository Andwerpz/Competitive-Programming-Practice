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

//Codeforces - 2006C

//My guess:
//consider the gcd of all the differences in an array. The array is brilliant if and only if the gcd is a
//power of 2 or 0. 

//It's pretty easy to show that if the gcd is not a power of 2 or 0, then it's never brilliant, but I couldn't
//figure out how to show the contrapositive. 

//Assuming that the above is correct, we can solve in O(n * log(n)^2) time using segment tree and two pointers.
//we just need to find the count of subarrays with gcd of differences that is not a power of 2, since if you 
//expand a subarray with gcd a power of 2, then it'll always remain a power of 2. 

//special consideration needs to be made for gcd = 0 and subarrays of single elements. 

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
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = n;
        vi diff(0);
        int pind = 0;
        for(int i = 1; i < n; i++){
            if(a[i] == a[i - 1]) {
                ans += i - pind;
            }
            else {
                pind = i;
            }
            diff.push_back(abs(a[i - 1] - a[i]));
        }
        n = diff.size() + 1;
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return gcd(a, b);};
        Segtree<int> segt(n - 1, 0, 0, fmodify, fcombine); 
        segt.assign(diff);
        int r = 0;
        for(int i = 0; i < n - 1; i++){
            while(r != n - 1 && (r == i || __builtin_popcount(segt.query(i, r)) != 1)) {
                r ++;
            }
            if(__builtin_popcount(segt.query(i, r)) == 1){
                ans += n - r;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}