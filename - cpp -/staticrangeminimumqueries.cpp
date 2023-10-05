#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1647

//segment tree problem. 

struct Segtree {
    //note that t[0] is not used
    int n;
    int* t;
    int uneut, qneut;

    //single element modification function
    function<int(int, int)> fmodify;

    //product of two elements for query and updating tree
    function<int(int, int)> fcombine;

    Segtree(int n, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int)> fcombine) {
        this -> n = n;
        t = new int[2 * n];

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

    void modify(int p, int value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    int query(int l, int r) { // sum on interval [l, r)
        int res = qneut;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    Segtree segt(n, 0, 1e9, fmodify, fcombine); 
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        segt.modify(i, next);
    }
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        a --;
        cout << segt.query(a, b) << "\n";
    }
    
    return 0;
}