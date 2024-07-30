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

//Codeforces - 1968 G1, G2

//first notice that the prefix of each segment must be equal to the prefix of the entire string. So first
//we can compute for each suffix, the lcp with that suffix and the entire string. 

//Instead of iterating across the number of segments to split the string, we'll instead iterate across a 
//target lcp, and compute for each the maximum number of segments. 

//for a given target lcp k, we can maintain a set of indices such that the suffix at index i has lcp >= k
//with the entire string. Then, we can use a greedy method to find the maximum number of segments. Start
//a pointer ptr at 0, and look for the closest suffix after ptr which is in the set. This should run over all
//targets k from 1 to n in log(n)^2 time. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;

    //single element modification function
    function<T(T, T)> fmodify;

    //product of two elements for query and updating tree
    function<T(T, T)> fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
        }
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++){
            t[i + n] = arr[i];
        }
        build();
    }

    void build() { // build the tree after manually assigning the values.
        for (int i = n - 1; i > 0; i--) {   
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none) {
            return r_res;
        }
        if(r_none) {
            return l_res;
        }
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> calc_suffix_array(string s) {
    s += "$"; 
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

//kasai's algorithm
vector<int> calc_lcp_array(string s){
    vector<int> suf = calc_suffix_array(s);
    int n = s.size();
    int k = 0;
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);
    for(int i = 0; i < n; i++) {
        rank[suf[i]] = i;
    }
    for(int i = 0; i < n; i++, k? k-- : 0) {
        if(rank[i] == n - 1){
            k = 0;
            continue;
        }
        int j = suf[rank[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
    }
    return lcp;
}

struct LCP {
    int n;
    Segtree<int> segt;
    vector<int> ind_mp;
    LCP() {}
    LCP(string s) {
        n = s.size();
        vector<int> lcp = calc_lcp_array(s);
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        segt = Segtree<int>(n, 0, 1e9, fmodify, fcombine); 
        segt.assign(lcp);
        vector<int> suf = calc_suffix_array(s);
        ind_mp = vector<int>(n);
        for(int i = 0; i < n; i++){
            ind_mp[suf[i]] = i;
        }
    }

    int get_lcp(int a, int b) {
        if(a == b){
            return n - a;
        }
        int l = min(ind_mp[a], ind_mp[b]);
        int r = max(ind_mp[a], ind_mp[b]);
        return segt.query(l, r);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, ql, qr;
        cin >> n >> ql >> qr;
        string s;
        cin >> s;
        LCP lcp(s);
        vvi mp(n + 1);
        set<int> ind_set;
        for(int i = 0; i < n; i++){
            mp[lcp.get_lcp(0, i)].push_back(i);
            if(lcp.get_lcp(0, i) != 0){
                ind_set.insert(i);
            }
        }
        vi ans(n + 1, 0);  
        for(int i = 1; i <= n; i++){
            int x = 0;
            int ptr = 0;
            while(ind_set.lower_bound(ptr) != ind_set.end()) {
                x ++;
                ptr = *ind_set.lower_bound(ptr) + i;
            }
            ans[x] = i;
            for(int j = 0; j < mp[i].size(); j++){
                ind_set.erase(mp[i][j]);
            }
        }
        for(int i = n - 1; i >= 0; i--){
            ans[i] = max(ans[i], ans[i + 1]);
        }
        for(int i = ql; i <= qr; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}