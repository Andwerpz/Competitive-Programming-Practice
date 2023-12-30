#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1896D

//single modify, range query
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

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        Segtree<int> segt(n, 0, 0, fmodify, fcombine);    //assignment modify, sum query
        set<int> ones;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            segt.modify(i, a);
            if(a == 1) {
                ones.insert(i);
            }
        }
        for(int i = 0; i < q; i++){
            int type;
            cin >> type;
            if(type == 1){
                int s;
                cin >> s;
                int tot = segt.query(0, n);
                if(tot < s){
                    cout << "NO\n";
                    continue;
                }
                if(ones.size() != 0){
                    int l = *ones.begin();
                    int r = *ones.rbegin();
                    int l_sum = segt.query(l, n);
                    int r_sum = segt.query(0, r + 1);
                    if(s <= l_sum || (s - l_sum) % 2 == 0 || s <= r_sum || (s - r_sum) % 2 == 0) {
                        cout << "YES\n";
                        continue;
                    }
                }
                else {
                    cout << (s % 2 == 0? "YES" : "NO") << "\n";
                    continue;
                }
                cout << "NO\n";
                continue;
            }
            else {
                int ind, v;
                cin >> ind >> v;
                ind --;
                if(segt.query(ind) == 1){
                    ones.erase(ind);
                }
                if(v == 1){
                    ones.insert(ind);
                }
                segt.modify(ind, v);
            }
        }
    }
    
    return 0;
}
