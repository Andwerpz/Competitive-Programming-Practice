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

//Codeforces - 2138B

//guessforces lmao. problem was missing the fact that you can only do the type 2 swap at most once, however
//I guessed the solution and it worked. 

//we can do inversion counting to figure out when the type 2 swap is useful. Turns out on a triple, the type 2 
//swap is only helpful if it's ordered like
// 3 2 1

//so, we just have to detect within the subarray if there is any 3 numbers that form a decreasing subsequence. 
//we can check for every midpoint, the closest number to its left and right that are greater and less than it
//and then populate a segment tree for fast subarray queries. 

//single modify, range query
template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
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
        int n, q;
        cin >> n >> q;
        vi p(n);
        for(int i = 0; i < n; i++) {
            cin >> p[i];
            p[i] --;
        }
        //segt[i] = what's the minimum left bound such that if you contain this element, the segment is still perfect
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return max(val, src);};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        Segtree<int> segt(n, 0, -1e9, fmodify, fcombine); 
        vi ord(n);
        for(int i = 0; i < n; i++) ord[i] = i;
        sort(ord.begin(), ord.end(), [&p](int a, int b) -> bool {
            return p[a] > p[b];
        });
        set<int> lo, hi;
        for(int i = 0; i < n; i++) lo.insert(i);
        for(int i = 0; i < n; i++) {
            int cur = ord[i];
            lo.erase(cur);  
            int rind = -1, lind = -1;
            {
                auto ptr = lo.lower_bound(cur);
                if(ptr != lo.end()) rind = *ptr;
            }
            {
                auto ptr = hi.lower_bound(cur);
                if(ptr != hi.begin()) {
                    ptr --;
                    lind = *ptr;
                }
            }
            if(rind != -1 && lind != -1) segt.modify(rind, lind + 1);
            hi.insert(cur);
        }
        // for(int i = 0; i < n; i++) cout << segt.query(i) << "\n";
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            l --;
            // cout << "VAL : " << segt.query(l, r) << "\n";
            if(segt.query(l, r) <= l) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    
    return 0;
}