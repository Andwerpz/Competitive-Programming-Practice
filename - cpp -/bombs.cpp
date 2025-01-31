#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
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

//Codeforces - 1326E

//i get the feeling that the intended solution is much more elegant than the one i cobbled together here. 
//eh, kinda. It still involves range queries and would probably be much faster. 

//First, observe that the answer will never increase when we add a bomb. This motivates some sort of two pointers solution
//where we iterate through the bombs in order while also keeping track of the current answer with another pointer. 

//Actually, we can make an even stronger statement. If an element is taken with k bombs, it will still be taken with k + 1
//bombs. Therefore for our two pointers solution, we'll increase the amount of bombs until the current answer gets taken, then
//decrement the answer by 1.

//When we decrement the current answer, we'll say that we put in a 'bomb request' on the position of the next answer. This
//request will extend from the next answer position all the way to the end of the array. Putting in new bombs can nullify this request
//only if the new bomb is after where the bomb request starts. 

//Since we want for the bombs to be associated with the elements they are actually deleting, if a bomb happens to make another bomb
//not needed, we should remove the other bomb. 

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
    
    int n;
    cin >> n;
    vi p(n), q(n), loc(n + 1);
    for(int i = 0; i < n; i++) cin >> p[i];
    for(int i = 0; i < n; i++) cin >> q[i];
    for(int i = 0; i < n; i++) {
        q[i] --;
        loc[p[i]] = i;
    }
    function<pii(pii, pii)> fmodify = [](const pii src, const pii val) -> pii{
        return {src.first + val.first, src.second};
    };
    function<pii(pii, pii, int)> fmodifyk = [](const pii src, const pii val, const int k) -> pii{
        return {src.first + val.first, src.second};
    };
    function<pii(pii, pii)> fcombine = [](const pii a, const pii b) -> pii{
        return a.first == b.first? (pii){a.first, min(a.second, b.second)} : (a.first < b.first? a : b);
    };
    SegtreeLazy<pii> segt(n, {0, 0}, {1e9, 1e9}, {0, 0}, fmodify, fmodifyk, fcombine);
    {
        vector<pii> tmp(n);
        for(int i = 0; i < n; i++) tmp[i] = {0, i};
        segt.assign(tmp);
    }
    set<int> ub;    //unused bombs
    vector<int> ans(n - 1, 1);
    ans[0] = n;
    int aptr = n;
    segt.modify(loc[n], n, {1, 0});
    for(int i = 0; i < n - 1; i++){
        if(segt.query(q[i]).first == 0) ub.insert(q[i]);
        else {
            segt.modify(q[i], n, {-1, 0});
            if(segt.query(q[i], n).first == -1) {
                int ind = segt.query(q[i], n).second;
                segt.modify(ind, n, {1, 0});
                ub.insert(ind);
            }
        }
        while(segt.query(n - 1).first == 0) {
            aptr --;
            segt.modify(loc[aptr], n, {1, 0});
            if(ub.lower_bound(loc[aptr]) != ub.end()) {
                int ind = *ub.lower_bound(loc[aptr]);
                ub.erase(ind);
                segt.modify(ind, n, {-1, 0});
            }
        }
        ans[i + 1] = aptr;
    }
    for(int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}