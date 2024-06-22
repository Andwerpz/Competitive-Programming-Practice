#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1976D

//instead of '(' and ')', we can use 1 and -1. Then, inverting the some subarray just means multiplying the subarray by -1. 
//notice that now, a subarray containing a good bracket sequence must sum to 0, and prefix of a good bracket sequence
//must sum to >= 0. 

//From here, we can observe a few constraints on what subarrays we can flip:
//1. the subarray must sum to 0; if it didn't, then the entire array would no longer be a good bracket sequence. 
//2. due to number 1, the prefix sums on the beginning and end of the subarray must be the same. 
//3. if the subarray is [l, r), then for any i in [l, r), pfx[i + 1] - pfx[l] <= pfx[l]. 
//in fact, if these 3 are followed, then the subarray is always good to flip. 

//to keep track of the first 2 constraints, for each value of pfx[i], we can keep track of how many we've seen. 
//for constraint 3, we can keep track of the last index that we've seen pfx[i], and maintain a segment tree to do 
//range max queries. 

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
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        int ptr = 0;
        vector<int> p(n, -1);
        vector<ll> cnt(n, 0);
        ll ans = 0;
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        Segtree<int> segt(n, 0, -1e9, fmodify, fcombine); 
        for(int i = 0; i < n; i++){
            ptr += (s[i] == '('? 1 : -1);
            segt.modify(i, ptr);
            if(p[ptr] == -1){
                p[ptr] = i;
                cnt[ptr] = 1;
                continue;
            }
            if(segt.query(p[ptr], i) > ptr * 2) {
                cnt[ptr] = 0;
            }
            ans += cnt[ptr];
            cnt[ptr] ++;
            p[ptr] = i;
        }
        cout << ans << "\n";
    }
    
    return 0;
}