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

//Codeforces - 1304 F1, F2

//the idea is that we can do dp and account for the overcounting caused by the cameras overlapping. 

//dp[i][j] = max animal sum so far where it's currently day i, and the last camera range is [j, j + k). 
//in order to compute dp[i][j], we need to look at the maximum out of all dp[i - 1], so we probably
//want to start with some sort of segment tree. From here on out, when i say range j, i mean the range
//starting from j.

//to account for doublecounting, we can use range increment supported by lazy segment tree. Consider 
//some element j of day i. The ranges that intersect it from the previous day are j - k + 1, j - k, 
//..., j. Therefore, if we're computing the dp value of a range that intersects j, we would want to subtract
//a[i][j] from the range j - k + 1 of the previous dp before taking the max. 

//if we compute the dp values from left to right sequentially, we only need to add and then subtract
//each element of a[i] once from the segment tree. Therefore, the complexity is O(nm * log(m)). 

//apparently there is also a O(nm) solution using monotonic stack, but that's too smart for me. 

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            this -> fmodify = fmodify;
            this -> fmodifyk = fmodifyk;
            this -> fcombine = fcombine;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n; i++){
                t[i + n] = initVal;
            }
            build();
        }

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++){
                t[i + n] = arr[i];
            }
            build();
        }

        //build tree after manually assigning values
        void build() {
            for(int i = n - 1; i > 0; i--){
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
            return _query(ind, ind + 1, 0, n, 1);
        }

    private:
        //calculates value of node based off of children
        //k is the amount of values that this node represents. 
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k / 2);
            push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change llo this node
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, int k) {
            if(!upd[ind]) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr) {
                apply(ind, val);
                push(ind, tr - tl);
                return;
            }
            int mid = tl + (tr - tl) / 2;
            if(l < mid) {
                _modify(l, min(r, mid), val, tl, mid, ind * 2);
            }
            if(r > mid) {
                _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            }
            combine(ind, tr - tl);
        }

        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r){
                return qneut;
            }  
            if(upd[ind]) {
                push(ind, tr - tl);
            }
            if(l == tl && r == tr){
                return t[ind];
            }
            int mid = tl + (tr - tl) / 2;
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vvi a(n + 1, vi(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    vvi pfx(n + 1, vi(m + 1, 0));
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= m; j++){
            pfx[i][j] = pfx[i][j - 1] + a[i][j - 1];
        }
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
    SegtreeLazy<int> segt(m - k + 1, 0, -2e9, 0, fmodify, fmodifyk, fcombine);
    vvi dp(n, vi(m - k + 1, 0));
    //base cases
    for(int i = 0; i < m - k + 1; i++){
        dp[0][i] = pfx[0][i + k] - pfx[0][i];
        dp[0][i] += pfx[1][i + k] - pfx[1][i];
    }
    for(int i = 1; i < n; i++){
        //init segtree
        segt.assign(dp[i - 1]);
        for(int j = 0; j < k; j++){
            int l = j - k + 1;
            segt.modify(max(0, l), min(m - k + 1, l + k), -a[i][j]);
        }
        for(int j = 0; j < m - k + 1; j++){
            dp[i][j] = pfx[i][j + k] - pfx[i][j] + segt.query(0, m - k + 1);
            dp[i][j] += pfx[i + 1][j + k] - pfx[i + 1][j];
            //update doublecounting
            {
                int l = j - k + 1;
                segt.modify(max(0, l), min(m - k + 1, l + k), a[i][j]);
            }
            if(j + k < m){
                int l = j + 1;
                segt.modify(l, min(m - k + 1, l + k), -a[i][j + k]);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < dp[n - 1].size(); i++){
        ans = max(ans, dp[n - 1][i]);
    }
    cout << ans << "\n";
    
    return 0;
}