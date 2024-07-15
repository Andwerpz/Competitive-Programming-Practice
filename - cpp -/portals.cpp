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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1271D

//notice that if you're going to defend castle i, then you always want to defend it as late as possible. 
//with this, we have a relatively simple O(n * C) dynamic programming approach, where C is the maximum number
//of warriors available to you. 

//my implementation uses lazy segment tree to get O(n * log(n)) complexity (well, if you ignore how many portals
//the input can throw at you). The idea is that each castle puts a constraint on how many warriors can be used
//in the prefix. If we use a warrior at castle i, then the constraint will decrease by 1 in the range [i, n).
//And if the constraint ever goes negative, that's invalid. 

//From here, just greedily try to hold the castles with the maximum importance value. 

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
    vi a(n), b(n), c(n);
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i] >> c[i];
    }
    vector<vi> port(n, vi(0));
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        port[u].push_back(v);
    }
    for(int i = 0; i < n; i++){
        port[i].push_back(i);
    }
    int ans = 0;
    vi mxp(n, -1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < port[i].size(); j++){
            int next = port[i][j];
            mxp[next] = i;
        }
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    SegtreeLazy<int> segt(n, 0, 1e9, 0, fmodify, fmodifyk, fcombine);
    {
        vi tmp(n, 0);
        int bsum = k;
        for(int j = 0; j < n; j++){
            bsum += b[j];
        }
        int mn = bsum;
        for(int j = n - 1; j >= 0; j--){
            tmp[j] = mn;
            bsum -= b[j];
            mn = min(mn, bsum - a[j]);
        }
        if(mn < 0){
            cout << "-1\n";
            return 0;
        }
        segt.assign(tmp);
    }
    vector<pii> ord(0);
    for(int j = 0; j < n; j++){
        ord.push_back({c[j], mxp[j]});
    }
    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());
    for(int j = 0; j < ord.size(); j++){
        int ind = ord[j].second;
        int val = ord[j].first;
        if(segt.query(ind, n) == 0){
            continue;
        }
        segt.modify(ind, n, -1);
        ans += val;
    }
    cout << ans << "\n";
    
    return 0;
}