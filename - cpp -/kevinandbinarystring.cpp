#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 2061 F1

//not exactly sure how this works, but it works. 

//my strategy is to go from left to right in s, and check each character if it matches with t. If it doesn't, 
//then we just swap this character's segment with the next segment. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s, t;
        cin >> s >> t;
        int n = s.size();
        map<int, int> seg;
        for(int i = 0; i < n;){
            int r = i;
            while(r != n && s[r] == s[i]) r ++;
            seg[i] = r;
            i = r;
        }
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        SegtreeLazy<int> segt(n, 0, 1e9, 0, fmodify, fmodifyk, fcombine);
        for(int i = 0; i < n; i++){
            segt.modify(i, s[i] - '0');
        }
        bool is_valid = true;
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(segt.query(i) == t[i] - '0') continue;
            if(!seg.count(i)) {
                is_valid = false;
                break;
            }
            ans ++;
            int cval = segt.query(i);
            int l = i, r = seg[i];
            int nl = -1, nr = -1;
            int pl = -1, pr = -1;
            if(r != n){
                nl = r, nr = seg[nl];
            }
            if(l != 0) {
                auto ptr = seg.find(i);
                ptr --;
                pl = ptr->first, pr = ptr->second;
            }
            if(nl == -1) {
                is_valid = false;
                break;
            }
            segt.modify(l, l + (nr - nl), cval ^ 1);
            segt.modify(l + (nr - nl), nr, cval);
            seg.erase(l);
            seg.erase(nl);
            if(l != 0) {
                seg[pl] = l + (nr - nl);
            }
            else {
                seg[l] = l + (nr - nl);
            }
            if(nr != n){
                seg[l + (nr - nl)] = seg[nr];
                seg.erase(nr);
            }
            else {
                seg[l + (nr - nl)] = nr;
            }
        }
        cout << (is_valid? ans : -1) << "\n";
    }
    
    return 0;
}