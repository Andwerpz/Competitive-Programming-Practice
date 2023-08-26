#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1788E

//let pfx[i] be the sum of the first i elements of array a. 
//if pfx[r] - pfx[l] >= 0, then it means that the segment [l, r) is a valid segment. 

//first, lets come up with a naive dp solution, then optimize it using segment tree. 

//let dp[i] be the maximum value of f(S) on the subarray [0, i). To find the value of dp[i], we can either just do
//nothing to the maximum segment from dp[i - 1], or for each j from 0 to i, if pfx[i] - pfx[j] >= 0, then we can
//update dp[i] with dp[j] + i - j. 

//now, this naive dp solution is O(n^2), and we can optimize it down to O(n * log(n)) using segment tree. 

//first, we can normalize pfx because we only care whether about the relative size of values in pfx. 
//next, we create a range increment modify, range max query segment tree; segt. After we compute dp[i], we can update the segt value
//at pfx[i] with dp[i]. Querying for the max in the range [0, pfx[i]] will tell you the maximum dp value with a pfx index less than i, but
//we still need to account for the i - j part. This can be done by just adding 1 to the entire range; [0, n), before querying every time. 

struct SegtreeLazy {
    public:
        int n;
        int* t;    //stores product of range
        int* d;    //lazy tree
        bool* upd;   //upd[i] = true if t[i] needs to be updated
        int uneut, qneut;

        //single element modify
        function<int(int, int)> fmodify;

        //k element modify
        function<int(int, int, int)> fmodifyk;

        //product of two elements for query
        function<int(int, int)> fcombine;

        SegtreeLazy(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
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

            t = new int[n * 2];
            d = new int[n * 2];
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

        void modify(int l, int r, int val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        int query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
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

        //registers a lazy change into this node
        void apply(int ind, int val) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> pfx(n + 1, 0);
    for(int i = 1; i <= n; i++){
        pfx[i] = pfx[i - 1] + a[i - 1];
    }
    //normalize pfx. 
    {
        map<ll, int> m;
        for(int i = 0; i < pfx.size(); i++){
            m.insert({pfx[i], 0});
        }
        int ptr = 0;
        for(auto i = m.begin(); i != m.end(); i++){
            i -> second = ptr ++;
        }
        for(int i = 0; i < pfx.size(); i++){
            pfx[i] = m.find(pfx[i]) -> second;
        }
    }
    vector<int> dp(n + 1, 0);
    //increment modify, maximum query
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
    SegtreeLazy segt(n + 1, 0, -1e9, fmodify, fmodifyk, fcombine);
    segt.modify(0, segt.n, -1e9);
    //base case
    segt.modify(pfx[0], pfx[0] + 1, -segt.query(pfx[0], pfx[0] + 1));
    for(int i = 1; i <= n; i++){
        segt.modify(0, segt.n, 1);
        dp[i] = max(segt.query(0, pfx[i] + 1), dp[i - 1]);
        segt.modify(pfx[i], pfx[i] + 1, -segt.query(pfx[i], pfx[i] + 1));
        segt.modify(pfx[i], pfx[i] + 1, dp[i]);
    }
    cout << dp[n] << "\n";
    
    return 0;
}
