#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1896E

//for each element in the array, a[i], we can identify it's destination; the index a[i]. 
//then, for each element in the array, we create a segment starting at the element and ending at it's destination. 

//every time we do an operation, all segments are going to shrink, unless the element is good, in which case
//it doesn't do anything. 

//we can observe that the number of operations for an element to become good is equal to the initial size of the
//segment minus the number of segments contained inside of it that become good before it. We can ignore the second
//condition, because if a segment is contained within another segment, then the inside segment will always become
//good before the outside one. 

//then, this is a classic segment problem, which can by sorting the segments, and using a segment tree. 

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
        if(p >= n){
            return;
        }
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) {
        if(l >= n){
            int b_l = l % n;
            int b_r = r - (l - b_l);
            return query(b_l, b_r);
        }
        if(r > n){
            return fcombine(_query(l, n), query(0, r - n));
        }
        return _query(l, r);
    }

    T query(int ind) {
        return _query(ind, ind + 1);
    }

    private:
        T _query(int l, int r) { // sum on interval [l, r)
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vector<int> d(n);
        for(int i = 0; i < n; i++){
            int tgt = a[i];
            if(tgt < i){
                tgt += n;
            }
            d[i] = tgt - i;
        }
        vector<int> ans(n, -1);
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        Segtree<int> segt(2 * n, 0, 0, fmodify, fcombine); 
        for(int i = 0; i < n; i++){
            segt.modify(i + n + d[i], 1);
        }
        for(int i = n - 1; i >= 0; i--){
            int cnt = segt.query(i, i + d[i]);
            ans[i] = d[i] - cnt;
            segt.modify(i + d[i], 1);
        }
        vector<int> actual_ans(n, -1);
        for(int i = 0; i < n; i++){
            actual_ans[a[i]] = ans[i];
        }
        for(int i = 0; i < n; i++){
            cout << actual_ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
