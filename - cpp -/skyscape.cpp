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

//Codeforces - 2084F

//observe that for every pair (i, j) where i < j, a[i] < a[j], then the two numbers a[i] and a[j] have to be 
//ordered ascending in the answer as well, let the answer be 'b'. There are no other restrictions. 

//So for every element from 1 to n, we can compute where it can be placed according to the already placed 
//elements in b. Actually, for every element, it turns out the valid positions always form a contiguous subrange
//of b, for i let's call this [l_i, r_i]. The intuition is that it's bounded to the left by lower elements to the 
//left in a, and bounded to the right by higher elements to the right in a. 

//we can compute all such ranges in O(n * log(n)) time using a min or max segment tree. Just need to iterate 
//through elements in ascending order and insert them into the segt if they're already placed in b. 

//Now, we have a bunch of ranges, and for each range we need to place one element. This sounds very much like
//a classic greedy problem, we can just sort all the ranges in ascending order of their right bound, and then
//greedily place the elements as far left as possible. 

//but there is one issue: placing elements might affect the ranges of subsequent elements. If we place some element
//x and then want to place y where x < y and r_x < r_y, then l_y may be affected by the position of x. Actually, 
//it's not that big of a deal, since l_x <= l_y anyways, so placing x will not 'cut off' portions of segments
//that come afterwards. You just need to ensure that if two segments have the same r, then you also sort by 
//the value. 

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

bool check_good(int n, vi a, vi ans) {
    if(ans[0] == -1) return true;
    // cout << "CHECK" << endl;
    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << "\n";
    // for(int i = 0; i < n; i++) cout << ans[i] << " ";
    // cout << endl;
    for(int i = 0; i < n; i++) a[i] --;
    for(int i = 0; i < n; i++) ans[i] --;
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    Segtree<int> segt(n, 0, 1e9, fmodify, fcombine); 
    segt.assign(a);
    vi apos(n);
    for(int i = 0; i < n; i++) apos[a[i]] = i;
    for(int i = 0; i < n; i++){
        // cout << "QUERY : " << segt.query(0, apos[ans[i]]) << endl;
        if(segt.query(0, apos[ans[i]]) < ans[i]) return false;
        segt.modify(apos[ans[i]], 1e9);
    }
    return true;
}

vi solve(int n, vi a, vi b) {
    for(int i = 0; i < n; i++) a[i] --;
    for(int i = 0; i < n; i++) b[i] --;
    vi apos(n), bpos(n, -1);
    for(int i = 0; i < n; i++) apos[a[i]] = i;
    for(int i = 0; i < n; i++) if(b[i] != -1) bpos[b[i]] = i;
    //for each element, find left and rightmost valid placeable position in b
    vi l(n, -1), r(n, -1);
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
    Segtree<int> segt(n, 1e9, 1e9, fmodify, fcombine); 
    for(int i = 0; i < n; i++){
        l[i] = max(0, -segt.query(0, apos[i]) + 1);
        if(bpos[i] != -1) segt.modify(apos[i], -bpos[i]);
    }
    for(int i = 0; i < n; i++) segt.modify(i, 1e9);
    for(int i = n - 1; i >= 0; i--){
        r[i] = min(n, segt.query(apos[i] + 1, n));
        if(bpos[i] != -1) segt.modify(apos[i], bpos[i]);
    }
    // for(int i = 0; i < n; i++) cout << l[i] << " " << r[i] << "\n";
    //do greedy.
    set<int> s;
    for(int i = 0; i < n; i++) if(b[i] == -1) s.insert(i);
    vector<pair<int, pii>> seg; //{r, {val, l}}
    for(int i = 0; i < n; i++) seg.push_back({r[i], {i, l[i]}});
    sort(seg.begin(), seg.end());
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        int cl = seg[i].second.second;
        int cr = seg[i].first;
        int val = seg[i].second.first;
        if(bpos[val] != -1) {
            //already placed
            if(bpos[val] < cl || bpos[val] >= cr) {
                is_valid = false;
                break;
            }
        }
        else {
            if(s.lower_bound(cl) == s.end()) {
                is_valid = false;
                break;
            }
            int ind = *s.lower_bound(cl);
            if(ind >= cr) {
                is_valid = false;
                break;
            }
            s.erase(ind);
            b[ind] = val;
        }
    }
    for(int i = 0; i < n; i++) b[i] ++;
    // for(int i = 0; i < n; i++) cout << b[i] << " ";
    // cout << endl;
    if(is_valid) return b;
    return {-1};
}

vi genperm(int n) {
    vi p(n);
    for(int i = 0; i < n; i++) p[i] = i + 1;
    // Initialize random number generator
    std::random_device rd;  // get a random seed
    std::mt19937 g(rd());   // Mersenne Twister RNG
    shuffle(p.begin(), p.end(), g);
    return p;
}

pair<vi, vi> gentc(int n) {
    vi a = genperm(n), b = genperm(n);
    int thresh = rand() % (1 << 16);
    // cout << "THRESH : " << thresh << "\n";
    for(int i = 0; i < n; i++) {
        // cout << "RAND : " << rand() % (1 << 16) << "\n";
        if(rand() % (1 << 16) > thresh) b[i] = 0;
    }
    return {a, b};
}

void run_test() {
    srand(time(0));
    int cnt = 0;
    while(true) {
        // cout << "CNT : " << cnt << endl;
        int n = 100;
        pair<vi, vi> ret = gentc(n);
        vi a = ret.first, b = ret.second;
        vi ans = solve(n, a, b);
        // if(ans[0] != -1) {
        //     cout << n << "\n";
        //     for(int i = 0; i < n; i++) cout << a[i] << " ";
        //     cout << "\n";
        //     for(int i = 0; i < n; i++) cout << b[i] << " ";
        //     cout << "\n";
        //     for(int i = 0; i < n; i++) cout << ans[i] << " ";
        //     cout << endl;
        // }
        if(!check_good(n, a, ans)) {
            cout << "BAD!!\n";
            cout << n << "\n";
            for(int i = 0; i < n; i++) cout << a[i] << " ";
            cout << "\n";
            for(int i = 0; i < n; i++) cout << b[i] << " ";
            cout << "\n";
            for(int i = 0; i < n; i++) cout << ans[i] << " ";
            cout << "\n";
            break;
        }
        cnt ++;
        if(cnt % 1000 == 0) cout << "CNT : " << cnt << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // run_test();
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        vi ans = solve(n, a, b);
        for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}