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

//Meta Hacker Cup 2025 Round 3 - B

//dp[i][j] = min cost
// considered up to ith lamp
// maximum run so far is of size j

//don't take next lamp
//dp[i][j] -> dp[i + 1][j]

//next run is of size k
//dp[i][j] -> dp[i + k][max(j, k)] + a[i, i + k)
//only makes sense to consider k > j

//going backwards, 
// dp[i][j] <- dp[i - j][x | x < j] + a[i - j, i)
// dp[i][j] <- dp[i - 1][j]

//have to be careful that a transition doesn't accidentally violate a b[i] requirement
//can ensure this by observing that for some b[i], if your last run ended within b[i] of i, and 
//you don't have a run of length b[i] yet, then that state is already invalid. 

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

    ifstream in("streetlamp_safety_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        int n;
        cin >> n;
        vl a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        {
            function<int(int, int)> fmodify = [](const int src, const int val) -> int{return max(src, val);};
            function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return max(src, val);};
            function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
            SegtreeLazy<int> segt(n, 0, 0, 0, fmodify, fmodifyk, fcombine);
            for(int i = 0; i < n; i++) {
                int l = i - b[i] + 1;
                int r = i + 1;
                segt.modify(l, r, b[i]);
            }
            for(int i = 0; i < n; i++) {
                b[i] = segt.query(i);
            }
        }
        //dp[i][j] = min cost
        // considered up to ith lamp
        // maximum run so far is of size j
    
        //don't take next lamp
        //dp[i][j] -> dp[i + 1][j]

        //next run is of size k
        //dp[i][j] -> dp[i + k][max(j, k)] + a[i, i + k)
        //only makes sense to consider k > j

        //going backwards, 
        // dp[i][j] <- dp[i - j][x | x < j] + a[i - j, i)
        // dp[i][j] <- dp[i - 1][j]
        vl pfx(n + 1, 0);
        for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + a[i - 1];
        vector dp(n + 1, vl(n + 1, 1e18));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j]);
            }
            for(int j = 1; j <= n; j++) {
                dp[i - 1][j] = min(dp[i - 1][j], dp[i - 1][j - 1]);
            }
            for(int j = 1; i - j >= 0; j++) {
                dp[i][j] = min(dp[i][j], dp[i - j][j - 1] + (pfx[i] - pfx[i - j]));
            }
            //eliminate invalid states
            for(int j = 0; j < b[i - 1]; j++) {
                dp[i][j] = 1e18;
            }

            // for(int j = 0; j <= n; j++) {
            //     cout << (dp[i][j] == 1e18 ? -1 : dp[i][j]) << " ";
            // }
            // cout << "\n";
        }
        ll ans = 1e18;
        for(int i = 0; i <= n; i++) ans = min(ans, dp[n][i]);
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}