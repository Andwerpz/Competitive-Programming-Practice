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

//AtCoder - ARC88E

//First, checking whether a string can be turned into a palindrome via swaps is easy. If we count the occurrences 
//for each character, a palindrome can have at most 1 character occur an odd number of times, so if we see more 
//than one odd character count, we can immediately return -1. Otherwise, it's always possible. 

//Now we just have to minimize the amount of swaps required. First, we need to get an equal amount of occurrences
//of all letters on both halves of the string. Since swapping two of the same letter is always a wasted swap, we
//can greedily assign the first half of occurrences of each letter to the front half, and the rest to the back half.
//Computing the number of swaps required is also easy, for each letter in the front half, just check how many 
//letters belonging to the back half are to the left of it. 

//Finally, we have to make sure that the two halves orders match. My guess here is that we can arbitrarily pick
//one of the halves, and sort it according to the other half. We can use a range sum query segment tree to do this 
//part in n * log(n) time. 

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
    
    string s;
    cin >> s;
    int n = s.size();
    vi f(26, 0);
    for(int i = 0; i < n; i++){
        f[s[i] - 'a'] ++;
    }
    int ocnt = 0;
    for(int i = 0; i < 26; i++){
        ocnt += f[i] % 2;
    }
    if(ocnt > 1) {
        cout << "-1\n";
        return 0;
    }
    int mid = -1;
    vb is_left(n, false);
    vi cf = f;
    vi a, b;
    for(int i = 0; i < n; i++){
        int c = s[i] - 'a';
        cf[c] --;
        if(f[c] % 2 && f[c] / 2 == cf[c]) {
            mid = i;
        }
        else if(cf[c] >= f[c] / 2) {
            is_left[i] = true;
            a.push_back(c);
        }
        else {
            b.push_back(c);
        }
    }
    ll ans = 0, rcnt = 0;
    for(int i = 0; i < n; i++){
        if(i == mid) continue;
        if(is_left[i]) {
            ans += rcnt;
            if(mid != -1 && i > mid) ans ++;
        }   
        else {
            rcnt ++;
            if(mid != -1 && i < mid) ans ++;
        }
    }
    reverse(b.begin(), b.end());
    vector<queue<int>> p(26);
    for(int i = 0; i < b.size(); i++) {
        p[b[i]].push(i);
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    Segtree<int> segt(n, 0, 0, fmodify, fcombine); 
    for(int i = 0; i < n; i++){
        segt.modify(i, 1);
    }
    for(int i = 0; i < a.size(); i++){
        int ind = p[a[i]].front();
        p[a[i]].pop();
        ans += segt.query(0, ind);
        segt.modify(ind, 0);
    }
    cout << ans << "\n";
    
    return 0;
}