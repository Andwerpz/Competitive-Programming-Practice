#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1938D

//first, notice that if the two multisets of elements of a and b are not the same, then it's always impossible. 
//next, define the size of an operation as the value of r - l. I claim that if it's possible to sort, we can always 
//sort using size 1 swaps. 

//observe that we can always make the first n - 2 elements of a match up with b with size 1 swaps. We can do this by
//sorting the first n - 2 elements of a like normal, but for p and q, always selecting the last 2 elements of b. 
//then, once the prefix of a matches up with b, i claim that there's nothing we can do about the last 2 elements, 
//so if they're not correct now, then it's impossible to make a match b. 

//proof has something to do with parity?

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

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
        }
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, arr.size()); i++){
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
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        map<int, int> am, bm;
        for(int i = 0; i < n; i++){
            am[a[i]] ++;
            bm[b[i]] ++;
        }
        bool alot = false;
        bool is_valid = true;
        for(auto i = am.begin(); i != am.end(); i++){
            if(bm[i->first] != am[i->first]) {
                is_valid = false;
            }
            if(am[i->first] > 1){
                alot = true;
            }
        }
        if(!is_valid) {
            cout << "NO\n";
            continue;
        }
        if(alot || n == 1) {
            cout << "YES\n";
            continue;
        }
        bool ord = true;
        for(int i = 0; i < n; i++){
            if(a[i] == b[n - 1] || a[i] == b[n - 2]) {
                ord = a[i] == b[n - 2];
                break;
            }
        }
        map<int, int> ind_mp;
        for(int i = 0; i < n; i++){
            ind_mp[a[i]] = i;
        }
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        Segtree<int> segt(n, 0, 0, fmodify, fcombine); 
        for(int i = 0; i < n - 2; i++){
            int ind = ind_mp[b[i]];
            int swaps = ind - segt.query(0, ind);
            if(swaps % 2) {
                ord = !ord;
            }
            segt.modify(ind, 1);
        }
        cout << (ord? "YES" : "NO") << "\n";
    }
    
    return 0;
}