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

//Codeforces - 992E

//bruh, off by one. Off by bruh (on gyatt!!) no cyapp

//let's try to search for the earliest king shaman in the array. 

//let's first have a pointer, p, that keeps track of the prefix that we already know there is 
//no king shaman. Then, the next king shaman must have value at least equal to the prefix sum
//up until p. So, just find the first value after p with value >= pfx[p]. 

//if this value works, then great, but if it doesn't, then we need to update p to be the
//prefix ending on the element we just found, and try again. 

//note that since the prefix sum will at least double every time, we'll have to iterate
//this at most log(1e9) times, and if we can efficiently find the next candidate shaman
//in log(n) time, then we'll have a O(n * log(n) * log(1e9)) solution. 

//I couldn't figure out how to find the next in log(n) time, so instead I opted to find it
//in log(n)^2 time, and it barely passed. We can just binary search and use a max segtree. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
    Segtree<ll> segt_sum(n, 0, 0, fmodify, fcombine); 
    function<ll(ll, ll)> fmodify1 = [](const ll src, const ll val) -> ll{return val;};
    function<ll(ll, ll)> fcombine1 = [](const ll a, const ll b) -> ll{return max(a, b);};
    Segtree<ll> segt_max(n, 0, 0, fmodify1, fcombine1); 
    segt_sum.assign(a);
    segt_max.assign(a);
    set<int> pans;
    for(int i = 0; i < q; i++){
        ll p, x;
        cin >> p >> x;
        p --;
        segt_sum.modify(p, x);
        segt_max.modify(p, x);
        if(segt_sum.query(0) == 0){
            cout << "1\n";
            continue;
        }
        while(pans.size() != 0 && p <= *(pans.rbegin())) {
            pans.erase(pans.lower_bound(p));
        }
        if(pans.size() != 0){
            cout << *pans.begin() + 1 << "\n";
            continue;
        }
        int ans = -1;
        int ptr = 0;
        while(ptr < n - 1) {
            ll tgt = segt_sum.query(0, ptr + 1);
            // cout << "TGT : " << tgt << "\n";
            int low = ptr + 1;
            int high = n - 1;
            int ind = high;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(segt_max.query(ptr + 1, mid + 1) >= tgt) {
                    ind = mid;
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            // cout << "IND : " << ind << "\n";
            // cout << "SM : " << segt_sum.query(0, ind) << " " << segt_max.query(ind) << "\n";
            if(segt_sum.query(0, ind) == segt_max.query(ind)) {
                ans = ind + 1;
                break;
            }
            ptr = ind;
        }
        if(ans != -1){
            pans.insert(ans - 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}