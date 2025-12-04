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

//ICPC Vietnam National Programming Contest 2025 - G

//kinda annoying implementation. 

//given a string, we can make it k-good by just looking at all contiguous runs of the same character, and truncating
//them down to length k. So the minimum amount of removals is simply \sum_{s} max(0, len(s) - k), where s iterates
//across all maximal contiguous runs, len(s) gets their length. 

//if we keep track of the lengths of these runs in some range query datastructure, we can answer queries of
//type 2 in O(log(n)) time. Now, the difficult part is actually keeping track of these lengths. 

//we can keep track of all the segments in a set, and queries of type 1 manifest as adding and removing segments from the
//set. You have to be careful to handle merging adjacent segments of the same color, and also implement it in such a way
//that each operation is amortized O(log(n)).

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

    int n, q;
    cin >> n >> q;
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return a + b;};
    Segtree<ll> fsegt(n + 1, 0, 0, fmodify, fcombine), ssegt(n + 1, 0, 0, fmodify, fcombine); 
    set<pair<pii, char>> s; //{{l, len}, char}
    int lsum = 0;
    auto ins_s = [&](pair<pii, char> p) {
        assert(!s.count(p));
        s.insert(p);
        int len = p.first.second;
        fsegt.modify(len, 1);
        ssegt.modify(len, len);
        lsum += len;
    };  
    auto rm_s = [&](pair<pii, char> p) {
        assert(s.count(p));
        s.erase(p);
        int len = p.first.second;
        fsegt.modify(len, -1);
        ssegt.modify(len, -len);
        lsum -= len;
    };
    auto rm_seg = [&](int l) -> void {
        assert(l != 0);
        auto ptr = s.lower_bound({{l, -1}, 'A'});
        assert((*ptr).first.first == l);
        pair<pii, char> ent = *ptr;
        int len = ent.first.second;
        assert(l != 0);
        assert(ptr != s.begin());
        ptr --;
        pair<pii, char> bent = *ptr;
        //remove this entry
        rm_s(ent);
        //extend previous entry
        rm_s(bent);
        bent.first.second += len;
        ins_s(bent);            
    };
    auto set_seg = [&](int l, int r, char c) -> void {
        vi to_rm;
        auto ptr = s.lower_bound({{l, -1}, 'A'});
        char rcol;
        if(ptr != s.begin()) {
            ptr --;
            rcol = ptr->second;
            ptr ++;
        }
        else {
            assert(ptr != s.end());
            rcol = ptr->second;
        }
        while(ptr != s.end() && (*ptr).first.first <= r) {
            if((*ptr).first.first >= l && (*ptr).first.first != 0) {
                to_rm.push_back((*ptr).first.first);
                rcol = (*ptr).second;
            }
            ptr ++;
        }
        for(int x : to_rm) rm_seg(x);
        ptr = s.lower_bound({{l, -1}, 'A'});
        if(ptr != s.begin()) ptr --;
        pair<pii, char> bent = *ptr;
        int bl = bent.first.first;
        int br = bl + bent.first.second;
        char bc = bent.second;
        assert(bl <= l);
        rm_s(bent);
        if(br - r > 0) {
            if(rcol == c) r = br;
            else ins_s({{r, br - r}, rcol});
        }
        if(bl < l) {
            if(bc == c) l = bl;
            else ins_s({{bl, l - bl}, bc});   
        }
        ins_s({{l, r - l}, c});
    };
    ins_s({{0, n}, 'A'});
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int l, r;
            char c;
            cin >> l >> r >> c;
            r ++;
            set_seg(l, r, c);
        }
        else {
            int k;
            cin >> k;
            ll ans = ssegt.query(k + 1, n + 1) - fsegt.query(k + 1, n + 1) * k;
            cout << ans << "\n";
        }
        assert(lsum == n);
    }
    
    return 0;
}