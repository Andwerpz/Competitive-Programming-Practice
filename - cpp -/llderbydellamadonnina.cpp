#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//SWERC 2021-2022 L

//on a high level, this problem can be solved using dp, dp[i] = max points after observing the kick
//given by pair i. So, dp[i] = max(dp[j]) + 1, where we can get from pair j to pair i. Naively, we can 
//solve this in n^2 time by considering for every i, every j that can get to it, but we need something like
//n * log(n) to not TLE. 

//first, we can force v = 1 by just scaling all the times by v, or t[i] := t[i] * v. 
//next, observe that it is possible to get from pair j to pair i if
//t[i] - t[j] >= |a[i] - a[j]|
//or equivalently
//t[i] - t[j] >= a[i] - a[j]
//t[i] - t[j] >= a[j] - a[i]

//t[i] - a[i] >= t[j] - a[j]
//t[i] + a[i] >= t[j] + a[j]

//if we plot the above two inequalities, with t on the y axis and a on the x axis, then we notice that for 
//a given t[i] and a[i], the region of pairs which can get to i is the 90 degree triangle below (a[i], t[i]). 
//The problem with this is that doing range queries over a triangle is pretty hard. 

//instead, we can rotate all the points by 90 degrees, and then the 90 degree triangle becomes a quadrant, 
//much easier for range queries. 

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

int lf_fg(vector<ll>& a, ll val) {
    if(a[a.size() - 1] <= val) {
        return a.size();
    }
    int low = 0;
    int high = a.size() - 1;
    int ans = high;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(a[mid] > val) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, v;
    cin >> n >> v;
    vector<pair<pair<ll, ll>, int>> a(n);  //{x, y}
    for(int i = 0; i < n; i++){
        cin >> a[i].first.second;
    }
    for(int i = 0; i < n; i++) {
        cin >> a[i].first.first;
    }
    n ++;
    a.push_back({{0, 0}, 0});   //base case
    //set v = 1 by scaling y by v
    for(int i = 0; i < n; i++){
        a[i].first.second *= v;
    }
    //rotate by 45 degrees clockwise
    //x = y + x;
    //y = y - x;
    for(int i = 0; i < n; i++){
        ll x = a[i].first.first;
        ll y = a[i].first.second;
        a[i].first.first = y + x;
        a[i].first.second = y - x;
    }
    //index points by x
    sort(a.begin(), a.end(), [](auto a, auto b) -> bool {
        return a.first.first < b.first.first;
    });
    vector<ll> xcoord(n);
    for(int i = 0; i < n; i++){
        a[i].second = i;
        xcoord[i] = a[i].first.first;
    }
    //iterate through points by increasing y
    function<ll(ll, ll)> fmodify = [](const ll src, const ll val) -> ll{return val;};
    function<ll(ll, ll)> fcombine = [](const ll a, const ll b) -> ll{return max(a, b);};
    Segtree<ll> segt(n, -1e9, 0, fmodify, fcombine); 
    sort(a.begin(), a.end(), [](auto a, auto b) -> bool {
        if(a.first.second == b.first.second) {
            return a.first.first < b.first.first;
        }
        return a.first.second < b.first.second;
    });
    for(int i = 0; i < n; i++){
        if(a[i].first.first == 0 && a[i].first.second == 0){
            //base case
            segt.modify(a[i].second, 0);
            continue;
        }
        int c_ans = segt.query(0, lf_fg(xcoord, a[i].first.first)) + 1;
        if(c_ans > 0) {
            segt.modify(a[i].second, c_ans);
        }
    }
    cout << segt.query(0, n) << "\n";
    
    return 0;
}
