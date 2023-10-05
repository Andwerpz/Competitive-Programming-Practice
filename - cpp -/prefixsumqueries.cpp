#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 2166

//we can simulate these updating prefix sums using a lazy segment tree. 

template <typename T>
struct SegtreeLazy {
    public:
        T n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, T)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T, T)> fmodifyk, function<T(T, T)> fcombine) {
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

            //make sure to initialize values
            for(T i = 0; i < n * 2; i++){
                t[i] = uneut;
            }
            for(T i = 0; i < n * 2; i++){
                d[i] = uneut;
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
        void combine(int ind, T k) {
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
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        //k is the amount of values that this node represents. 
        void push(int ind, T k) {
            if(d[ind] == uneut) {
                return;
            }
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2;
                int r = ind * 2 + 1;
                apply(l, d[ind]);
                apply(r, d[ind]);
            }
            d[ind] = uneut;
        }

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(d[ind] != uneut) {
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

        T _query(int l, int r, int tl, int tr, T ind) {
            if(l == r){
                return qneut;
            }  
            if(d[ind] != uneut) {
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll, ll)> fmodifyk = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return max(a, b);};
    SegtreeLazy<ll> segt(n, 0, -1e18, fmodify, fmodifyk, fcombine);
    vector<ll> arr(n, 0);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        segt.modify(i, n, arr[i]);
    }
    for(int i = 0; i < q; i++){
        int type;
        cin >> type;
        if(type == 1){
            ll k, u;
            cin >> k >> u;
            k --;
            ll diff = u - arr[k];
            segt.modify(k, n, diff);
            arr[k] = u;
        }
        else if(type == 2){
            ll a, b;
            cin >> a >> b;
            a --;
            cout << max(0ll, segt.query(a, b) - (a == 0? 0 : segt.query(a - 1))) << "\n";
        }
    }
    
    return 0;
}
