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

//Codeforces - 2000H

//just a datastructure problem. 

//first, we can maintain a set of all elements. For the purposes of the '?' type queries, we want to keep
//track of the gaps between elements in the set, so we can keep another map that maps gap len -> set of
//elements that start gaps of that length. 

//Now, to answer type '?' queries, we just have to figure out the minimum element which starts a gap
//of length k or greater. This can be done using a minimum query segment tree. 

//maintaining these three things can be done in log(n) time per addition / removal. 

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

void upd_segt(map<int, set<int>>& lmp, Segtree<int>& segt, int diff, int val) {
    if(lmp[diff].count(val)) {
        lmp[diff].erase(val);
        segt.modify(diff, lmp[diff].size() != 0? *lmp[diff].begin() : 1e9);
    }
    else {
        lmp[diff].insert(val);
        segt.modify(diff, *lmp[diff].begin());
    }   
}

void add_val(set<int>& s, map<int, set<int>>& lmp, Segtree<int>& segt, int val) {
    auto rptr = s.upper_bound(val);
    auto lptr = rptr;
    lptr --;
    if(rptr != s.end()) {
        upd_segt(lmp, segt, *rptr - *lptr - 1, *lptr);
        upd_segt(lmp, segt, *rptr - val - 1, val);
    }
    upd_segt(lmp, segt, val - *lptr - 1, *lptr);
    s.insert(val);
}

void rm_val(set<int>& s, map<int, set<int>>& lmp, Segtree<int>& segt, int val) {
    s.erase(val);
    auto rptr = s.upper_bound(val);
    auto lptr = rptr;
    lptr --;
    upd_segt(lmp, segt, val - *lptr - 1, *lptr);
    if(rptr != s.end()) {
        upd_segt(lmp, segt, *rptr - val - 1, val);
        upd_segt(lmp, segt, *rptr - *lptr - 1, *lptr);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    Segtree<int> segt(2e6 + 100, 1e9, 1e9, fmodify, fcombine); 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> s;
        s.insert(0);
        map<int, set<int>> lmp;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            add_val(s, lmp, segt, a);
        }
        int m;
        cin >> m;
        for(int i = 0; i < m; i++){
            string type;
            cin >> type;
            int x;
            cin >> x;
            if(type == "+") {
                add_val(s, lmp, segt, x);
            }
            else if(type == "-") {
                rm_val(s, lmp, segt, x);
            }
            else if(type == "?") {
                int ans = segt.query(x, 2e6 + 50);
                if(ans == 1e9){
                    ans = *s.rbegin();
                }
                ans ++;
                cout << ans << " ";
            }
        }
        cout << "\n";
        {
            vi tmp(0);
            for(auto i = s.begin(); i != s.end(); i++){
                tmp.push_back(*i);
            }
            for(int i = 0; i < tmp.size(); i++){
                if(tmp[i] == 0){
                    continue;
                }
                rm_val(s, lmp, segt, tmp[i]);
            }
        }
    }
    
    return 0;
}