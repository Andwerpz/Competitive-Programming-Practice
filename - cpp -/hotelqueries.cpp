#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1143

//we can use a range max query segment tree to binary search for the first hotel that has enough
//capacity. 

//segment tree should also support single element increment modify to update the capacity. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    T n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree(T n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
    Segtree<int> segt(n, 0, -1e9, fmodify, fcombine);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        segt.modify(i, next);
    }
    for(int i = 0; i < m; i++){
        int next;
        cin >> next;
        if(segt.query(0, n) < next) {
            cout << "0 ";
            continue;
        }
        int low = 1;
        int high = n;
        int ans = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(segt.query(0, mid) >= next) {
                ans = min(ans, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        cout << ans << " ";
        segt.modify(ans - 1, -next);
    }
    cout << "\n";
    
    return 0;
}
