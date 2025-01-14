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

//AtCoder - AGC7D

//First, note that the problem gives a partial score for solving it with the additional constraint that n <= 2000, 
//so let's first consider an n^2 solution before optimizing it down. 

//What you first notice is that the optimal strategy for picking up the coins goes something like this: 
// - travel some amount to the right, ending on a bear. You should feed each bear you come across. 
// - turn around, travelling back to the first bear you fed, and wait until it drops its coin
// - turn back around and keep collecting coins until you get to the last bear you fed

//Naturally, we can come up with a dp solution to this problem: dp[i] = minimum amount of time required to get to the exit
//after collecting the first i coins and ending at the ith bear. Transitions are just testing each size of group to
//simultaneously collect, and we pick the minimum one. 

//Now, how do we optimize this to do n <= 10^5? If we can compute each dp state in better than linear time, then our 
//solution will be fast enough. Notice that to compute each dp[i], it's essentially just a range minimum query, where we
//add to each element some amount based off of the distance to the ith bear. We can use a lazy segment tree to do 
//range minimum queries in O(log(n)) time, and update the segment tree in amortized O(log(n)) time as well. 

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

void solve_slow(ll n, ll e, ll t, vl& a) {
    vl dp(n + 1, 1e18);
    dp[n] = e - a[n];   //just go to exit
    for(int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j <= n; j++){
            ll dist = a[j] - a[i + 1];
            ll cost = a[i + 1] - a[i];  //constant
            cost += dist;   //factor in
            cost += max(dist * 2, t);   //split into two parts
            dp[i] = min(dp[j] + cost, dp[i]);
        }
    }
    cout << dp[0] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, e, t;
    cin >> n >> e >> t;
    vl a(n);
    for(ll& x : a) cin >> x;
    a.push_back(0);
    sort(a.begin(), a.end());
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll, int)> fmodifyk = [](const ll src, const ll val, const int k) -> ll{return src + val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return min(a, b);};
    SegtreeLazy<ll> dp(n + 1, 0, 1e18, 0, fmodify, fmodifyk, fcombine);
    dp.modify(n, e - a[n]); //just go to exit
    vl dpa(n);
    int rptr = n + 1;
    for(int i = n - 1; i >= 0; i--){
        //extend r boundary
        while(rptr != 0 && (a[rptr - 1] - a[i + 1]) * 2 >= t) {
            rptr --;
            dp.modify(rptr, (a[rptr] - a[i + 1]) * 2);
        }
        //query value
        dpa[i] = min(dp.query(i + 1, rptr) + t, dp.query(rptr, n + 1));
        dpa[i] += a[i + 1] - a[i];
        dp.modify(i, dpa[i]);
        //prep for next
        dp.modify(i + 1, n + 1, a[i + 1] - a[i]);
        dp.modify(rptr, n + 1, (a[i + 1] - a[i]) * 2);
    }
    cout << dpa[0] << "\n";
    
    return 0;
}