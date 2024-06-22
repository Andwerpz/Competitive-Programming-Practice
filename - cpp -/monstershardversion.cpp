#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1786E

//first, notice that for any set of monsters, it's always optimal to first do a bunch of type 1 operations, 
//then do 1 type 2 operation to kill all of the remaining monsters. 

//let's denote the array of monsters A. First, sort A in ascending order. Notice then, we want to use type 1 operations
//to lower the health of each monster low enough that it is just one above the preceding monster (so that we can use a 
//type 2 operation to kill them all). Let's denote the target health of A[i] as B[i]. 

//B[0] = 1, since we need a monster to start off the chain, and in general, B[i] = min(A[i], B[i - 1] + 1)

//I say that an element of A[i] is redundant if we can remove it, and the answer doesn't change. We can see that if
//A[i] == B[i], then it is redundant, and we can remove it. Probably a more useful fact is that if i + 1 > A[i], then 
//it is redundant, for the first i. In other words, if the amount of numbers less than equal to you is greater than
//your value, then you are redundant, if you are the first element that satisfies this condition from the left. 

//finally, if there are no redundant elements, then the answer is simply sum(A) - sum(B), and we can note that sum(B) is just
//the sequence 1, 2, 3, ..., given no redundant elements. 

//To solve the problem, we will go from left to right, and add elements into A, every time we add, we recompute the answer.
//In order to quickly identify redundant elements, we can use a lazy segment tree that supports range increment, and
//range minimum index query. Initially, T[i] = i, which means that element i can have at most i other elements less than
//or equal to it. When adding some element u, we increment the range [u, n] with -1. If some T[j] == -1, then we know that
//there is a redundant element equal to j in A, and we can just remove it by incrementing [j, n] by 1. 

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
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        struct seg {
            int mn, ind;
            seg() {
                mn = 1e9;
                ind = 0;
            }
            seg(int _mn, int _ind) {
                mn = _mn;
                ind = _ind;
            }
            seg(int val) {
                mn = val;
            }
        };
        vector<seg> init_arr(n + 1);
        for(int i = 0; i <= n; i++){
            init_arr[i] = seg(i, i);
        }
        function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
            return seg(src.mn + val.mn, src.ind);
        };
        function<seg(seg, seg, int)> fmodifyk = [](const seg src, const seg val, const int k) -> seg{
            return seg(src.mn + val.mn, src.ind);
        };
        function<seg(seg, seg)> fcombine = [](const seg a, const seg b) -> seg{
            if(a.mn == b.mn) {
                return seg(a.mn, min(a.ind, b.ind));
            }
            return a.mn < b.mn? seg(a.mn, a.ind) : seg(b.mn, b.ind);
        };
        SegtreeLazy<seg> segt(n + 1, seg(0), seg(), seg(), fmodify, fmodifyk, fcombine);
        segt.assign(init_arr);
        ll ans = 0;
        ll cnt = 0;
        for(int i = 0; i < n; i++){
            //add a[i]
            ans += a[i];
            cnt ++;
            ans -= cnt;
            segt.modify(a[i], n + 1, seg(-1));
            seg q = segt.query(0, n + 1);
            if(q.mn == -1){
                //remove q.ind
                ans -= q.ind;
                ans += cnt;
                cnt --;
                segt.modify(q.ind, n + 1, seg(1));
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}