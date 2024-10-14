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

//Codeforces - 2009 G1 G2

//only solves easy and hard versions D:

//for each index, we can compute the minimum cost to make a k-consecutive sequence ending at
//that index. The idea is that if we subtract i from every a[i], then k-consecutive sequences will look
//like k consecutive identical numbers. Then, the minimum cost to make i be the end of a 
//k-consecutive sequence is simply k minus the maximum frequency of any number occurring within
//the k numbers before i. 

//we can precompute the answers to every i, eans[i], and this actually solves the easy version 
//outright. 

//for the hard version, we notice that we must return some sort of sum range sum of eans, but more
//specifically, it's a range sum of minimums. 

//to solve, we can maintain a lazy segment tree that supports range assignments. Simply sort all the
//queries in descending order of left bound, and update the segment tree accordingly. 

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
    
    int t;
    cin >> t;
    while(t--){
        int n, k, q;
        cin >> n >> k >> q;
        vector<int> a(n), eans(n, 1e9);
        map<int, int> fmap, ffmap;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] -= i;
            ffmap[fmap[a[i]]] --;
            fmap[a[i]] ++;
            ffmap[fmap[a[i]]] ++;
            if(i >= k - 1){
                eans[i] = k - ffmap.rbegin()->first;
                ffmap[fmap[a[i - (k - 1)]]] --;
                if(ffmap[fmap[a[i - (k - 1)]]] == 0){
                    ffmap.erase(fmap[a[i - (k - 1)]]);
                }
                fmap[a[i - (k - 1)]] --;
                ffmap[fmap[a[i - (k - 1)]]] ++;
            }
        }
        function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
        function<ll(ll, ll, int)> fmodifyk = [](const ll src, const ll val, const int k) -> ll{return val * k;};
        function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
        SegtreeLazy<ll> segt(n, 0, 0, 0, fmodify, fmodifyk, fcombine);
        vi fless(n, n);
        {
            stack<pii> s;
            s.push({-1e9, n});
            for(int i = n - 1; i >= 0; i--){
                while(s.top().first >= eans[i]) {
                    s.pop();
                }
                fless[i] = s.top().second;
                s.push({eans[i], i});
            }
        }
        vector<pair<pii, int>> queries(q);
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            l --;
            queries[i] = {{l, r}, i};
        }
        sort(queries.begin(), queries.end());
        reverse(queries.begin(), queries.end());
        vl ans(q, -1);
        int cl = n - k + 1;
        for(int i = 0; i < q; i++){
            int l = queries[i].first.first;
            int r = queries[i].first.second;
            int ind = queries[i].second;
            while(cl > l) {
                cl --;
                segt.modify(cl + k - 1, fless[cl + k - 1], eans[cl + k - 1]);
            }
            ans[ind] = segt.query(l + k - 1, r);
        }
        for(int i = 0; i < q; i++){
            cout << ans[i] << "\n";
        }
    }
    
    return 0;
}