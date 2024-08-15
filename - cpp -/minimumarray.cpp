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

//Codeforces - 1887C

//let's keep a range increment segment tree that stores the difference between the current array (which is the array
//after processing the queries), and the lexicographically minimum array so far. Initially all elements in the segment
//tree should be 0. 

//after applying an operation, we can determine if the current array is lexicographically less than our current best
//array by seeing if the first non-zero element is negative. If it is, then we can simply say that the current array is
//our new best array, and set all elements to 0 in the segt. 

//This solution is correct, however it is too slow, specifically finding the first non-zero element. This can be fixed
//by observing that lexicographically minimizing the array is identical to minimizing the difference array. The difference
//array D of A is simply D[0] = A[0], D[i] = A[i] - A[i - 1]. This allows us to not have to do range queries, instead we
//only need to modify 2 elements for every query, allowing us to maintain a segment tree that can tell us the first
//non-zero element in log(n) time. 

//one note on reducing implementation headache. Instead of also having to support the assginment operation in order to 
//set all elements to 0 when we find a new best, we can simply just undo the operations that we have done since we
//last found the new best. Since all operations are performed at most twice, this doesn't change the complexity. 

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

void solve() {
    int n;
    cin >> n;
    //increment modify, first non-zero element query
    function<pair<ll, pll>(pair<ll, pll>, pair<ll, pll>)> fmodify = [](pair<ll, pll> src, pair<ll, pll> val) -> pair<ll, pll>{
        ll nval = src.first + val.first;
        return {nval, {src.second.first, nval != 0? src.second.first : 1e9}};
    };
    function<pair<ll, pll>(pair<ll, pll>, pair<ll, pll>)> fcombine = [](pair<ll, pll> a, pair<ll, pll> b) -> pair<ll, pll>{
        return {a.first + b.first, {a.second.first, min(a.second.second, b.second.second)}};
    };
    Segtree<pair<ll, pll>> segt(n + 1, {0, {}}, {0, {0, 1e9}}, fmodify, fcombine); //{value, {index, first nonzero index}}
    {
        vector<pair<ll, pll>> init(n, {0, {0, 0}});
        for(int i = 0; i < n; i++){
            init[i].second.first = i;
            init[i].second.second = 1e9;
        }
        segt.assign(init);
    }
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int q;
    cin >> q;
    int lex_mind = 0;
    vvi qa(q, vi(3));
    for(int i = 0; i < q; i++){
        int l, r, x;
        cin >> l >> r >> x;
        l --;
        qa[i] = {l, r, x};
        segt.modify(l, {x, {}});
        segt.modify(r, {-x, {}});
        int fnon = segt.query(0, n).second.second;
        if(fnon >= n || segt.query(fnon).first >= 0){
            continue;
        }
        for(int j = lex_mind; j <= i; j++){
            int _l = qa[j][0];
            int _r = qa[j][1];
            int _x = qa[j][2];
            segt.modify(_l, {-_x, {}});
            segt.modify(_r, {_x, {}});
        }
        lex_mind = i + 1;
    }
    vl ans(n + 1, 0);
    for(int i = 0; i < lex_mind; i++){
        int _l = qa[i][0];
        int _r = qa[i][1];
        int _x = qa[i][2];
        ans[_l] += _x;
        ans[_r] -= _x;
    }
    for(int i = 1; i <= n; i++){
        ans[i] += ans[i - 1];
    }
    for(int i = 0; i < n; i++){
        ans[i] += a[i];
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    
    return 0;
}