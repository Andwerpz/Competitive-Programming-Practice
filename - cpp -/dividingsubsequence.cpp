#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC133B

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

        for(int i = 0; i < 2 * n; i++){
            t[i] = uneut;
        }
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
        T res = qneut;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                res = fcombine(res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res = fcombine(res, t[r]);
            }
        }
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    //max assignment modify, max query
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return max(src, val);};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
    Segtree<int> segt(n, -1e9, -1e9, fmodify, fcombine); 
    vector<int> p(n);
    vector<int> q(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }
    for(int i = 0; i < n; i++){
        cin >> q[i];
    }
    vector<int> q_ind(n + 1);   //value to index
    for(int i = 0; i < n; i++){
        q_ind[q[i]] = i;
    }
    for(int i = 0; i < n; i++){
        int val = p[i];
        vector<int> poss(0); //index
        for(int j = val; j <= n; j += val) {
            poss.push_back(q_ind[j]);
        }   
        sort(poss.begin(), poss.end());
        reverse(poss.begin(), poss.end());
        //cout << "VAL : " << val << "\n";
        for(int j = 0; j < poss.size(); j++){
            int ind = poss[j];
            int dp_val = max(1, segt.query(0, ind) + 1);
            //cout << "IND : " << ind << " " << dp_val << " " << segt.query(0, ind) << "\n";
            segt.modify(ind, dp_val);
        }
    }
    cout << segt.query(0, n) << "\n";
    
    return 0;
}
