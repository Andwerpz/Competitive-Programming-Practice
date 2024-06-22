#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1520F2

//kinda annoying to implement, everyone should use exclusive right bound. 

//One naive approach is to just binary search for every query, but that will take around 10^4 * log2(2 * 10^5) or around
//10^5 queries (conservative estimate). 

//Instead, we can split the array into chunks of size 16. At the beginning, we'll expend n / 16 queries to figure out how many
//zeroes are in each of these chunks, then when we want to answer a query, we can just locate the chunk that the kth zero is
//supposed to be in, and binary search through that chunk. 

//The amount of queries we'll use is 2 * 10^5 / 16 + 10^4 * 4, or around 52500 queries. 

//be careful when implementing the binary search for the chunks, as it's pretty easy to have a case where it'll take 5 queries
//instead of 4 to find the answer. 

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
            for(int i = 0; i < min(n, arr.size()); i++){
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
    
    int n, t;
    cin >> n >> t;
    int k;
    cin >> k;
    //ok, 4 queries per section. that means each section can be 16 long
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    int nr_seg = (n + 15) / 16;
    SegtreeLazy<int> segt(nr_seg, 0, 0, 0, fmodify, fmodifyk, fcombine);
    //for each section, figure out how many 0s are there
    int prev = 0;
    for(int i = 0; i < nr_seg; i++){
        int l = i * 16;
        int r = min(l + 15, n - 1);
        l ++;
        r ++;
        cout << "? " << l << " " << r << endl;
        int cur;
        cin >> cur;
        int nr_zero = 16 - (cur - prev);
        segt.modify(i, nr_zero);
    }
    //handle queries
    for(int i = 0; i < t; i++){
        //binary search for the section that can contain the kth zero
        int sid = 0;
        {
            int low = 0;
            int high = nr_seg - 1;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(segt.query(0, mid) < k) {
                    sid = max(sid, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
        }
        //within this section, binary search for the exact position of the kth zero
        int ans = 15;
        {
            int base = sid * 16 + 1;
            int low = 0;
            int high = 14;
            if(high + base > n){
                high -= high + base - n;
            }
            while(low <= high) {
                int mid = low + (high - low) / 2;
                cout << "? " << 1 << " " << base + mid << endl;
                int cur;
                cin >> cur;
                cur = base + mid - cur;
                if(cur >= k){
                    ans = min(ans, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            ans += base;
        }
        cout << "! " << ans << endl;
        //update the array
        segt.modify(sid, -1);
        if(i != t - 1) {
            cin >> k;
        }
    }
    
    return 0;
}