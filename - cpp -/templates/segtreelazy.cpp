#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
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
            for(int i = 0; i < n * 2; i++){
                t[i] = uneut;
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

void print_segt(SegtreeLazy<int> segt) {
    cout << "PRINT SEGT : \n";
    int inc = 1;
    for(int i = 1; i < segt.n * 2;){
        int j = i;
        i += inc;
        inc *= 2;
        while(j < i){
            cout << segt.t[j] << " ";
            j ++;
        }
        cout << "\n";
    }
    cout << "\n";

    inc = 1;
    for(int i = 1; i < segt.n * 2;){
        int j = i;
        i += inc;
        inc *= 2;
        while(j < i){
            cout << segt.d[j] << " ";
            j ++;
        }
        cout << "\n";
    }
    cout << "\n";
}

void modify(vector<int>& a, int l, int r, int val, SegtreeLazy<int> segt) {
    for(int i = l; i < r; i++){
        a[i] = segt.fmodify(a[i], val);
    }
}

int query(vector<int>& a, int l, int r, SegtreeLazy<int> segt) {
    int ans = segt.qneut;
    for(int i = l; i < r; i++){
        ans = segt.fcombine(ans, a[i]);
    }
    return ans;
}

bool test_segt(SegtreeLazy<int> segt, int valInit) {
    int n = segt.n;
    vector<int> arr(n, valInit);
    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % (n + 1);
        int val = rand() % 10;
        if(rand() % 2 == 1){
            val *= -1;
        }
        if(l > r){
            swap(l, r);
        }
        modify(arr, l, r, val, segt);
        cout << "MODIFY " << l << " " << r << " " << val << "\n";
        segt.modify(l, r, val);

        if(rand() % 10 == 0){
            int ind = rand() % n;
            int val = segt.query(ind, ind + 1);
            modify(arr, ind, ind + 1, -val, segt);
            segt.modify(ind, ind + 1, -val);
            cout << "MODIFY " << ind << " " << ind + 1 << " " << -val << "\n";
        }
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
            print_segt(segt);
            return false;
        }
    }
    cout << "\n";
    return true;
}

void run_segt_tests(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
    srand(time(0));
    bool isValid = true;
    for(int i = 0; i < 100; i++){
        SegtreeLazy<int> segt(maxSize, updateNeutral, queryNeutral, fmodify, fmodifyk, fcombine);
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

    // -- ASSIGNMENT MODIFY, SUM QUERY --
    {
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val * k;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        run_segt_tests(n, 0, 0, fmodify, fmodifyk, fcombine);
    }

    // -- INCREMENT MODIFY, MINIMUM QUERY --
    // {
    //     function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    //     function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
    //     function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    //     run_segt_tests(n, 0, 1e9, fmodify, fmodifyk, fcombine);
    // }

    // -- ASSIGNMENT MODIFY, MINIMUM QUERY --
    // {
    //     function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    //     function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val;};
    //     function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    //     run_segt_tests(n, 0, 1e9, fmodify, fmodifyk, fcombine);
    // }

    return 0;
}


