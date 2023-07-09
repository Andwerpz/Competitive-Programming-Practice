#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range increment, range min
struct SegtreeLazy {
    public:
        int n;
        int* t;    //stores product of range
        int* d;    //lazy tree
        bool* upd;   //upd[i] = true if t[i] needs to be updated
        int uneut, qneut;

        SegtreeLazy(int maxSize, int updateNeutral, int queryNeutral, int valInit) {
            n = maxSize;
            uneut = updateNeutral;
            qneut = queryNeutral;

            //raise n to nearest pow 2
            int x = 1;
            while(x < n) {
                x <<= 1;
            }
            n = x;

            t = new int[n * 2];
            d = new int[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n * 2; i++){
                t[i] = valInit;
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        ~SegtreeLazy() {
            delete t;
            delete d;
            delete upd;
        }

        void modify(int l, int r, int val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        int query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

    private:
        //single element modify
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};

        //k element modify
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};

        //product of two elements for query
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};

        //calculates value of node based off of children
        void combine(int ind, int k) {
            if(ind >= n){
                return;
            }
            int l = ind * 2;
            int r = ind * 2 + 1;
            //make sure children are correct value before calculating
            push(l, k);
            push(r, k);
            t[ind] = fcombine(t[l], t[r]);
        }

        //registers a lazy change into this node
        void apply(int ind, int val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }

        //applies lazy change to this node
        void push(int ind, int k) {
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

        void _modify(int l, int r, int val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]){
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

        int _query(int l, int r, int tl, int tr, int ind) {
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
            int lans = qneut;
            int rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

void print_segt(SegtreeLazy segt) {
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
            cout << segt.upd[j] << " ";
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

void modify(vector<int>& a, int l, int r, int val) {
    for(int i = l; i < r; i++){
        a[i] += val;
    }
}

int query(vector<int>& a, int l, int r) {
    int ans = 1e9;
    for(int i = l; i < r; i++){
        ans = min(ans, a[i]);
    }
    return ans;
}

bool test_segt(int n) {
    SegtreeLazy segt(n, 0, 1e9, 0);
    vector<int> arr(n, 0);
    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % n;
        int val = 1;
        if(l > r){
            swap(l, r);
        }
        modify(arr, l, r, val);
        cout << "MODIFY " << l << " " << r << "\n";
        segt.modify(l, r, val);
        //print_segt(segt);
    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " \n"[i == n - 1];
    }

    bool isValid = true;
    for(int i = 0; i < n; i++){
        int l = rand() % n;
        int r = rand() % n;
        if(l > r){
            swap(l, r);
        }
        int arrmin = query(arr, l, r);
        int segtmin = segt.query(l, r);
        cout << "QUERY " << l << " " << r << ", ARR : " << arrmin << " SEGT : " << segtmin << "\n";
        if(arrmin != segtmin) {
            isValid = false;
        }
    }
    cout << "\n";
    return isValid;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    srand(time(0));
    
    bool isValid = true;
    for(int i = 0; i < 100; i++){
        if(!test_segt(100)) {
            isValid = false;
        }
    }
    if(isValid){
        cout << "TEST PASSED\n";
    }
    else {
        cout << "TEST FAILED\n";
    }

    return 0;
}


