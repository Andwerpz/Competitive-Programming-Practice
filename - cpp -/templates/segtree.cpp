#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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
};

void modify(vector<int>& a, int ind, int val, Segtree<int> segt) {
    a[ind] = segt.fmodify(a[ind], val);
}

int query(vector<int>& a, int l, int r, Segtree<int> segt) {
    int ans = segt.qneut;
    for(int i = l; i < r; i++){
        ans = segt.fcombine(ans, a[i]);
    }
    return ans;
}

bool test_segt(Segtree<int> segt, int valInit) {
    int n = segt.n;
    vector<int> arr(n, valInit);
    for(int i = 0; i < n; i++){
        int ind = rand() % n;
        int val = rand() % 10;
        modify(arr, ind, val, segt);
        cout << "MODIFY " << ind << " " << val << "\n";
        segt.modify(ind, val);
    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " \n"[i == n - 1];
    }

    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % (n + 1);
        if(l > r){
            swap(l, r);
        }
        int arrans = query(arr, l, r, segt);
        int segtans = segt.query(l, r);
        cout << "QUERY " << l << " " << r << ", ARR : " << arrans << " SEGT : " << segtans << "\n";
        if(arrans != segtans) {
            return false;
        }
    }
    cout << "\n";
    return true;
}

void run_segt_tests(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int)> fcombine) {
    srand(time(0));
    bool isValid = true;
    for(int i = 0; i < 100; i++){
        Segtree<int> segt(maxSize, updateNeutral, queryNeutral, fmodify, fcombine);
        if(!test_segt(segt, updateNeutral)) {
            cout << "TEST FAILED\n";
            return;
        }
    }
    cout << "TEST PASSED\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n = 100;

    // -- INCREMENT MODIFY, SUM QUERY -- 
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        run_segt_tests(n, 0, 0, fmodify, fcombine); 
    }

    // -- ASSIGNMENT MODIFY, MIN QUERY -- 
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        run_segt_tests(n, 0, 1e9, fmodify, fcombine); 
    }
    
    return 0;
}
