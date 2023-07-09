#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1842E

//dp + lazy segment tree to lower complexity to n*log(n)
//go read tutorial for better explanation, but tbh, i don't really understand what they are saying D:

//note that if two triangles touch, then it is always more efficient to just combine the two triangles. The cost 
//is less than or equal to the sum of costs of the two triangles, and you cover more area. 

//dp[i] = minimum cost to 'end' at i, assuming we don't overlap triangles. 

struct SegtreeLazy {
    public:
        ll n;
        ll* t;    //stores product of range
        ll* d;    //lazy tree
        bool* upd;   //upd[i] = true if t[i] needs to be updated
        ll uneut, qneut;

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

            t = new ll[n * 2];
            d = new ll[n * 2];
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

        void modify(int l, int r, ll val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        ll query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

    private:
        function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
        function<ll(ll, ll, ll)> fmodifyk = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
        function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return min(a, b);};

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

        //puts a lazy change into a node
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

        void _modify(int l, int r, ll val, int tl, int tr, int ind) {
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

        ll _query(int l, int r, int tl, int tr, int ind) {
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
            ll lans = qneut;
            ll rans = qneut;
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
    
    int n, k;
    ll A;
    cin >> n >> k >> A;
    SegtreeLazy seg(k + 1, 0, 2e9, 0);
    vector<vector<int>> a(0);
    for(int i = 0; i < n; i++){
        int x, y, c;
        cin >> x >> y >> c;
        int l = x;
        int r = l + (k - x - y);
        a.push_back({r, l, c});
        //cout << "SEGMENT : " << r << " " << l << " " << c << endl;
    }
    sort(a.begin(), a.end());
    int j = 0;
    for(int i = 1; i <= k; i++){
        //cout << "I : " << i << endl;
        //segment penalties
        ll skipPenalty = 0;
        ll skipans = seg.query(i - 1, i);
        while(j < a.size() && a[j][0] == i){
            int r = a[j][0];
            int l = a[j][1];
            ll c = a[j][2];
            j ++;
            //cout << "SEGMENT PENALTY : " << l + 1 << " " << r << " " << c << endl;
            seg.modify(l + 1, r, c);
            skipans += c;
        }
        //compute skip ans
        //cout << "PREV : " << seg.query(i - 1, i) << "\n";
        //cout << "SKIP PENALTY : " << skipPenalty << "\n";
        //triangle length penalty
        seg.modify(0, i, A);
        //cout << "PRINT MIN SEGTREE : \n";
        // for(int ptr = 0; ptr <= k; ptr++){
        //     cout << seg.query(ptr, ptr + 1) << " ";
        // }
        // cout << "\n";
        // cout << "PRINT SEGTREE BEFORE : \n";
        // seg.print();
        // cout << seg.query(0, i) << "\n";
        //minimum triangle ans
        ll trians = seg.query(0, i);
        //put ans into segtree
        //cout << "TENT ANS : " << skipans << " " << trians << "\n";
        ll curans = min(skipans, trians);
        seg.modify(i, i + 1, curans);
        //cout << "PRINT SEGTREE AFTER : \n";
        //seg.print();
    }
    cout << seg.query(k, k + 1) << "\n";
    
    return 0;
}
