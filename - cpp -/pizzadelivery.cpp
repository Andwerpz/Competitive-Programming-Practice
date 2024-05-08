#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - P

//given a distance, we can use sweepline to count how many pairs of points are less than or equal to that 
//distance apart in O(n * log(n)). 

//then, we can just binary search for the minimum distance. 

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
        l = max(l, 0);
        r = min(r, n);
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

ll do_test(vector<pair<int, int>>& a, int d) {
    // cout << "TEST : " << d << endl;
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    Segtree<int> segt(1e5 + 100, 0, 0, fmodify, fcombine); 
    int rptr = 0;
    ll ans = 0;
    for(int i = 0; i < a.size(); i++){
        while(rptr != a.size() && a[i].first - a[rptr].first > d) {
            segt.modify(a[rptr].second, -1);
            rptr ++;
        }
        ans += segt.query(a[i].second - d, a[i].second + d + 1);
        segt.modify(a[i].second, 1);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    int low = 0;
    int high = 1e6;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(do_test(a, mid) >= k) {
            ans = min(ans, mid);
            high = mid - 1;
        }   
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
