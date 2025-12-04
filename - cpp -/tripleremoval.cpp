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

//Codeforces - 2152C

//let Z, O, be the count of zeroes and ones in the array respectively. 
//first, it's possible to remove all elements iff Z and O are both divisible by 3. 
//next, the theoretical minimum score is simply Z / 3 + O / 3. We can achieve this if we spend exactly 1 cost on
//removing every 3 elements. 

//actually, if there is any triple initially where we can remove it with a cost of 1, then we can always guarantee
//the minimum possible score. We just have to use the initial triple to make the next triple cost 1. 

//finally, observe that if the initial triple isn't cost 1, we'll just use it to make all subsequent triples 
//cost 1. So for each subarray, we just want to find the pair of 0s or 1s that are closest together. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vi zp(n + 1, 0), op(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            zp[i] = zp[i - 1] + (a[i - 1] == 0);
            op[i] = op[i - 1] + (a[i - 1] == 1);
        }
        // cout << "PFX : \n";
        // for(int i = 0; i <= n; i++) cout << zp[i] << " ";
        // cout << "\n";
        // for(int i = 0; i <= n; i++) cout << op[i] << " ";
        // cout << endl;
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        Segtree<int> zsegt(n, 1e9, 1e9, fmodify, fcombine); 
        Segtree<int> osegt(n, 1e9, 1e9, fmodify, fcombine);
        int pz = -1, po = -1;
        set<int> zs, os;
        for(int i = 0; i < n; i++) {
            if(a[i] == 0) {
                zs.insert(i);
                if(pz != -1) {
                    zsegt.modify(pz, i - pz);
                }
                pz = i;
            }
            else {
                os.insert(i);
                if(po != -1) {
                    osegt.modify(po, i - po);
                }
                po = i;
            }
        }
        // for(int i = 0; i < n; i++) cout << zsegt.query(i) << " ";
        // cout << "\n";
        while(q--) {
            int l, r;
            cin >> l >> r;
            l --;
            int nz = zp[r] - zp[l];
            int no = op[r] - op[l];
            // cout << "TEST : " << zp[r] << " " << zp[l] << " " << l << " " << r << "\n";
            // cout << "TEST : " << op[r] << " " << op[l] << " " << l << " " << r << "\n";
            // cout << "NZ NO : " << nz << " " << no << endl;
            if((nz % 3) || (no % 3)) {
                cout << "-1\n";
                continue;
            }
            int cans = 1e9;
            if(nz != 0) {
                auto ptr = zs.lower_bound(r);
                assert(ptr != zs.begin());
                ptr --;
                assert(*ptr >= l);
                cans = min(cans, zsegt.query(l, *ptr));
                // cout << "QUERY : " << l << " " << *ptr << " " << zsegt.query(l, *ptr) << endl;
            }
            if(no != 0) {
                auto ptr = os.lower_bound(r);
                assert(ptr != os.begin());
                ptr --;
                assert(*ptr >= l);
                cans = min(cans, osegt.query(l, *ptr));
            }
            assert(cans != 1e9);
            cans += nz / 3 + no / 3 - 1;
            cout << cans << "\n";
        }
    }
    
    return 0;
}