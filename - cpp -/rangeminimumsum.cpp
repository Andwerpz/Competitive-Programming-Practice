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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1988E

//the idea is to first compute the answer without removing any elements, then modifying that answer for each element
//that we remove. 

//to compute the value normally, we can do a divide and conquer approach. To solve the problem on some segment [l, r), 
//we first find the minimum element on that segment, let the index be i. Then, consider how many subarrays that include
//that minimum element. Then, we can simply add to the answer the answers to ranges [l, i), and [i + 1, r). 

//let's say that we remove element a[i]. I'll only analyze what happens to elements to the left, but it's a similar 
//story for elements to the right of i. From now on, j < i. 

//note that the only elements that are affected by the removal of a[i] are the ones whos range sizes change due to
//it's removal. These are the elements that have a[i] inside their range, or directly bordering it. If you think
//about which elements these are, we can actually keep a monotonic stack to keep track of all of them. 

//the removal of a[i] will affect these elements differently depending on whether they are greater or less than a[i]. 
//If they are less than, then the removal will reduce the right size of the right side of the range by 1. If they 
//are greater, then removing a[i] will potentially increase the size of the range. 

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

Segtree<int> segt;
vi ind_mp;
vl tl, tr;

ll calc_orig(int l, int r) {
    if(l == r){
        return 0;
    }
    int val = segt.query(l, r);
    int ind = ind_mp[val];
    ll ans = (ll) (ind + 1 - l) * (ll) (r - ind) * val;
    tl[ind] = ind + 1 - l;
    tr[ind] = r - ind;
    // cout << "ANS : " << l << " " << r << " " << ans << "\n";
    ans += calc_orig(l, ind) + calc_orig(ind + 1, r);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ind_mp = vi(n + 1);
        tl = vl(n + 1), tr = vl(n + 1);
        for(int i = 0; i < n; i++){
            ind_mp[a[i]] = i;
        }
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        segt = Segtree<int>(n, 0, 1e9, fmodify, fcombine); 
        segt.assign(a);
        ll orig = calc_orig(0, n);
        function<ll(ll, ll)> fmodify_sum = [](const ll src, const ll val) -> ll{return val;};
        function<ll(ll, ll)> fcombine_sum = [](const ll a, const ll b) -> ll{return a + b;};
        Segtree<ll> s_less(n + 1, 0, 0, fmodify_sum, fcombine_sum), s_more(n + 1, 0, 0, fmodify_sum, fcombine_sum);
        vl ans(n, orig);
        stack<int> s;
        //forwards pass
        for(int i = 0; i < n; i++){
            //account for removing this element
            ans[i] -= tl[i] * tr[i] * a[i];
            // cout << "REMOVAL : " << tl[i] * tr[i] * a[i] << "\n";
            //update ans
            // cout << "ANS RINC : " << s_more.query(a[i], n + 1) - s_less.query(0, a[i]) << "\n";
            ans[i] += s_more.query(a[i], n + 1) - s_less.query(0, a[i]);
            //update stack
            while(s.size() != 0 && s.top() > a[i]) {
                int next = s.top();
                s.pop();
                s_less.modify(next, 0);
                s_more.modify(next, 0);
            }
            s.push(a[i]);
            // cout << "TL TR : " << a[i] << " " << tl[a[i]] << " " << tr[a[i]] << "\n";
            s_less.modify(a[i], tl[i] * a[i]);
            int rind = i + tr[i];
            if(rind >= n - 1 || a[rind + 1] < a[i]){
                continue;
            }
            ll extra;
            {
                int low = rind + 2;
                int high = n;
                int ans = low;
                while(low <= high) {
                    int mid = low + (high - low) / 2;
                    if(segt.query(rind + 1, mid) > a[i]) {
                        ans = max(ans, mid);
                        low = mid + 1;
                    }
                    else {
                        high = mid - 1;
                    }
                }
                extra = ans - (rind + 1);
            }
            // cout << "EXTRA : " << extra << " " << rind << "\n";
            s_more.modify(a[i], extra * a[i] * tl[i]);
        }
        s = stack<int>();
        for(int i = 0; i < n; i++){
            s_less.modify(i, 0);
            s_more.modify(i, 0);
        }
        //backwards pass
        for(int i = n - 1; i >= 0; i--){
            // cout << "ANS LINC : " << s_more.query(a[i], n + 1) - s_less.query(0, a[i]) << "\n";
            ans[i] += s_more.query(a[i], n + 1) - s_less.query(0, a[i]);
            while(s.size() != 0 && s.top() > a[i]) {
                int next = s.top();
                s.pop();
                s_less.modify(next, 0);
                s_more.modify(next, 0);
            }
            s.push(a[i]);
            s_less.modify(a[i], tr[i] * a[i]);
            int lind = i - tl[i];
            // cout << "TL : " << tl[i] << "\n";
            if(lind <= 0 || a[lind - 1] < a[i]){
                continue;
            }
            ll extra;
            {
                int low = 0;
                int high = lind - 1;
                int ans = high;
                while(low <= high) {
                    int mid = low + (high - low) / 2;
                    if(segt.query(mid, lind) > a[i]) {
                        ans = min(ans, mid);
                        high = mid - 1;
                    }
                    else {
                        low = mid + 1;
                    }
                }
                extra = lind - ans;
            }
            // cout << "EXTRA : " << extra << " " << lind << "\n";
            s_more.modify(a[i], extra * a[i] * tr[i]);
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}