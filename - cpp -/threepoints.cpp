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

//Topcoder - 11987

//pretty neat problem, there's probably some slick monotonic stack solution, but coming up with this 
//new lazy segment tree idea is also pretty cool. 

//If we index the points by their x coordinate, so a[i] = the y value of the ith point, then this problem is
//identical to counting the number of triples i < j < k such that a[i] < a[k] < a[j]. Since all a[i] are unique, 
//we can of course coordinate compress the points so that the values of a are within range [0, n)

//Consider fixing j and counting the amount of valid i, k. For each k to the right of j, we need to count the
//number of i to the left such that a[k] > a[i]. 

//If we iterate j from left to right, we can maintain an array 'gt', where gt[i] = the number of elements to the 
//left of j that the value i is greater than. Note that i is not an index, but a value. When adding some element
//to the left side (incrementing j) we can simply increment every gt[i] s.t. i > a[j]. This can be done quickly
//using lazy segment tree

//However, note that when incrementing j, we need to mark gt[a[j]] = 0, and then not increment it in any future
//increments. This can also be done quickly using a lazy segment tree. Finally, we can just do a range sum query
//to compute all the valid i, k, given some j. 

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;
        function<T(T, T)> fmodify, fcombine;
        function<T(T, T, int)> fmodifyk;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, T initVal, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
            uneut = updateNeutral, qneut = queryNeutral;
            this->fmodify = fmodify;
            this->fmodifyk = fmodifyk;
            this->fcombine = fcombine;
            n = 1; //raise n to nearest pow 2
            while(n < maxSize) n <<= 1;
            t = new T[n * 2], d = new T[n * 2];
            upd = new bool[n * 2];
            for(int i = 0; i < n; i++) t[i + n] = initVal;
            build();
        }
	
        //modifies the range [l, r)
        void modify(int l, int r, T val) {_modify(l, r, val, 0, n, 1);}
        void modify(int ind, T val) {modify(ind, ind + 1, val);}
        
        //queries the range [l, r)
        T query(int l, int r) {return _query(l, r, 0, n, 1);}
        T query(int ind) {return query(ind, ind + 1);}

        void assign(vector<T>& arr) {
            for(int i = 0; i < min(n, (int) arr.size()); i++) t[i + n] = arr[i];
            build();
        }
        void build() {
            for(int i = n - 1; i > 0; i--) t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            for(int i = 0; i < n * 2; i++){d[i] = uneut; upd[i] = false;}
        }

    private:
        void combine(int ind, int k) {
            if(ind >= n) return;
            int l = ind * 2, r = ind * 2 + 1;
            push(l, k / 2), push(r, k / 2);
            t[ind] = fcombine(t[l], t[r]);
        }
        void apply(int ind, T val) {
            upd[ind] = true;
            d[ind] = fmodify(d[ind], val);
        }
        void push(int ind, int k) {
            if(!upd[ind]) return;
            t[ind] = fmodifyk(t[ind], d[ind], k);
            if(ind < n) {
                int l = ind * 2, r = ind * 2 + 1;
                apply(l, d[ind]), apply(r, d[ind]);
            }
            upd[ind] = false;
            d[ind] = uneut;
        }
        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r) return;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) {apply(ind, val), push(ind, tr - tl); return;}
            int mid = tl + (tr - tl) / 2;
            if(l < mid) _modify(l, min(r, mid), val, tl, mid, ind * 2);
            if(r > mid) _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
            combine(ind, tr - tl);
        }
        T _query(int l, int r, int tl, int tr, int ind) {
            if(l == r) return qneut;
            if(upd[ind]) push(ind, tr - tl);
            if(l == tl && r == tr) return t[ind];
            int mid = tl + (tr - tl) / 2;
            T lans = qneut, rans = qneut;
            if(l < mid) lans = _query(l, min(r, mid), tl, mid, ind * 2);
            if(r > mid) rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            return fcombine(lans, rans);
        }
};

class ThreePoints {
public:
    ll countColoring(int n, ll xzero, ll xmul, ll xadd, ll xmod, ll yzero, ll ymul, ll yadd, ll ymod) {
        // {sum, nr ignoring elements}
        // modify is either increment all non-ignoring elements if val.second == 0, 
        // or toggling the ignoring state of all elements in range if val.second != 0
        function<pll(pll, pll)> fmodify = [](const pll src, const pll val) -> pll {
            if(val.second) return {src.first, 1 - src.second};
            else return {src.first + val.first * (1 - src.second), src.second};
        };
        function<pll(pll, pll, int)> fmodifyk = [](const pll src, const pll val, const int k) -> pll {
            if(val.second) return {src.first, k - src.second};
            else return {src.first + val.first * (k - src.second), src.second};
        };
        function<pll(pll, pll)> fcombine = [](const pll a, const pll b) -> pll{
            return {a.first + b.first, a.second + b.second};
        };
        SegtreeLazy<pll> segt(n, {0, 0}, {0, 0}, {0, 0}, fmodify, fmodifyk, fcombine);
        vector<pll> pts(n);
        pts[0] = {xzero, yzero};
        for(int i = 1; i < n; i++){
            pts[i].first = (pts[i - 1].first * xmul + xadd) % xmod;
            pts[i].second = (pts[i - 1].second * ymul + yadd) % ymod;
        }
        //sort by x, coordinate compress by y
        sort(pts.begin(), pts.end());
        vi a(n);
        {
            set<ll> s;
            for(int i = 0; i < n; i++) s.insert(pts[i].second);
            map<ll, int> imp;
            for(auto i = s.begin(); i != s.end(); i++) imp[*i] = imp.size();
            for(int i = 0; i < n; i++) a[i] = imp[pts[i].second];
        }
        //calc answer
        ll ans = 0;
        for(int i = 0; i < n; i++){
            //remove current element from right side
            ll oval = segt.query(a[i]).first;
            segt.modify(a[i], {-oval, 0});
            segt.modify(a[i], {0, 1});
            //increment answer
            ans += segt.query(0, a[i]).first;
            //add current element to left side
            segt.modify(a[i] + 1, n, {1, 0});
        }
        return ans;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg2;
    cin >> arg2;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg3;
    cin >> arg3;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg4;
    cin >> arg4;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg5;
    cin >> arg5;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg6;
    cin >> arg6;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg7;
    cin >> arg7;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int arg8;
    cin >> arg8;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = ThreePoints();
    long long ret = c.countColoring(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    cout << ret;
}