#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
using namespace std;
using vi = vector<int>;

//ICPC World Finals 2020 - D

//Use manacher to find for each index, the longest palindrome centered on that index. 

//then, just greedily take the smallest palindrome from the left and right sides until you can't anymore. 

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

        for(int i = 0; i < 2 * n; i++){
            t[i] = uneut;
        }
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
        T res = qneut;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                res = fcombine(res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res = fcombine(res, t[r]);
            }
        }
        return res;
    }
};

vector<vi> manacher(const string& s) {
    int n = s.size();
    vector<vi> p(2);
    p[0] = vi(n+1);
    p[1] = vi(n);

    for (int z = 0; z < 2; ++z) {
        for (int i = 0, l = 0, r = 0; i < n; ++i) {
            int t = r-i+ !z;
            if (i<r) p[z][i] = min(t, p[z][l+t]);
            int L = i - p[z][i], R = i+p[z][i] - !z;
            while (L >= 1 && R+1<n && s[L-1] == s[R+1]) 
                p[z][i]++, L--, R++;
            if (R > r) {
                l = L, r = R;
            }
        }
    }

    return p;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;

    int n = s.size();

    vector<vi> pals = manacher(s);
    reverse(s.begin(), s.end());
    vector<vi> revpals = manacher(s);
    reverse(revpals[0].begin(), revpals[0].end());

    // cerr << "PALS" << endl;
    // for (int i = 0; i < n; ++i) {
    //     cerr << pals[0][i] << " ";
    // }
    // cerr << endl;
    // cerr << endl;

    // cerr << "revPALS" << endl;
    // for (int i = 0; i < n; ++i) {
    //     cerr << revpals[0][i] << " ";
    // }
    // cerr << endl;
    // cerr << endl;
    int val = 0;
    for (int i = n-1; i > -1; --i) {
        revpals[0][i] = val;

    }

    vi dplr(n+1, 1e7);
    // function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
    // function<int(int, int)> fcombine_min = [](const int a, const int b) -> int{return min(a, b);};
    // Segtree<int> dplr(n + 1, 1e7, 1e9, fmodify, fcombine_min); 
    // function<int(int, int)> fcombine_max = [](const int a, const int b) -> int{return max(a, b);};
    // Segtree<int> dplr(n + 1, 0, 0, fmodify, fcombine_max); 
    // dplr[0] = 0;
    
    int left = 0, right = n-1;

    for (int i = 0; i < n; ++i) {
        // cerr << "LEFT : " << left << endl;
        if (pals[0][i] == 0) continue;
        if (i - pals[0][i] <= left) {
            // doable
            if (i + (i - left) - 1 <= right) {
                // doable
                left = i;
            }
        }
    }

    // cerr << "FINALL : " << left << endl;

    for (int i = n-1; i > -1; --i) {
        // cerr << "right : " << right << endl;
        if (pals[0][i] == 0) continue;
        if (i + pals[0][i] - 1 >= right) {
            if (i - (right - i) - 1 >= left) {
                right = i-1;
            }
        }
    }

    // cerr << "FINALR : " << right << endl;


    cout << right - left + 1 << endl;

    
    return 0;
}
