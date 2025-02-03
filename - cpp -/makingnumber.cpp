#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//2022-2023 Winter Petrozavodsk Camp Day 4 - F

//some annoying implementation. 

//Z will follow Y tightly until it can't anymore, then it switches to putting digits greedily 
//from lowest first. 

//We can keep track of the maximum common prefix between Z and Y in amortized O(1) time for each query.
//Next, when Z deviates from Y, the first deviation must be greater than whatever digit is in Y. 
//there are 3 cases: 
// - we can replace the digit after the common prefix
// - we can replace the last digit of the common prefix
// - we need to look somewhere in the common prefix to replace

//the first two are pretty simple. For the third one, we have to find the closest increase to 
//the end of the common prefix, and replace the lower element. 

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
    
    string x, y;
    cin >> x >> y;
    int n = x.size();
    int q;
    cin >> q;
    vi fx(10, 0), fy(10, 0);
    int tptr = 0;
    for(int i = 0; i < n; i++) fx[x[i] - '0'] ++;
    for(int i = 0; i < n; i++){
        if(fy[y[i] - '0'] + 1 > fx[y[i] - '0']) {
            break;
        }
        tptr = i + 1;
        fy[y[i] - '0'] ++;
    }
    // cout << "FY : \n";
    // for(int i = 0; i < 10; i++) cout << fy[i] << " ";
    // cout << "\n";
    set<int> inc;
    for(int i = 0; i < n - 1; i++){
        if(y[i] < y[i + 1]) inc.insert(i);
    }
    function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
    vector<Segtree<int>> f(10);
    for(int i = 0; i < 10; i++) f[i] = Segtree<int>(n, 0, 0, fmodify, fcombine);
    for(int i = 0; i < n; i++){
        f[y[i] - '0'].modify(i, 1);
    }
    // for(int i = 0; i < 10; i++){
    //     for(int j = 0; j < n; j++) {
    //         cout << f[i].query(0, j + 1) << " ";
    //     }
    //     cout << "\n";
    // }
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int ind, val;
            cin >> ind >> val;
            // cout << "CHANGE : " << ind << " " << val << "\n";
            ind --;
            if(ind != 0 && y[ind - 1] < y[ind]) inc.erase(ind - 1);
            if(ind != n - 1 && y[ind] < y[ind + 1]) inc.erase(ind);
            f[val].modify(ind, 1);
            f[y[ind] - '0'].modify(ind, -1);
            // cout << "OTPTR : " << tptr << "\n";
            // cout << "FX FY : \n";
            // for(int i = 0; i < 10; i++) cout << fx[i] << " ";
            // cout << "\n";
            // for(int i = 0; i < 10; i++) cout << fy[i] << " ";
            // cout << "\n";
            if(ind < tptr) {
                fy[val] ++;
                fy[y[ind] - '0'] --;
                y[ind] = val + '0';
                while(fy[val] > fx[val]) {
                    // cout << fy[val] << " " << fx[val] << " " << fy[y[tptr - 1] - '0'] << "\n";
                    tptr --;
                    fy[y[tptr] - '0'] --;
                }
            }
            y[ind] = val + '0';
            while(tptr != n && fy[y[tptr] - '0'] + 1 <= fx[y[tptr] - '0']) {
                fy[y[tptr] - '0'] ++;
                tptr ++;
            }
            // cout << "TPTR : " << tptr << endl;
            if(ind != 0 && y[ind - 1] < y[ind]) inc.insert(ind - 1);
            if(ind != n - 1 && y[ind] < y[ind + 1]) inc.insert(ind);
        }
        else {
            int ind;
            cin >> ind;
            ind --;
            //find where z stops matching y, and what the first non-matching element is
            int mptr = tptr, unm = -1;
            if(tptr == n) mptr = tptr, unm = 0;  //z = y
            else {
                //check if can just replace next element with something higher
                // cout << "CHECK NEXT\n";
                for(int i = 0; i < 10; i++){
                    if(i <= y[tptr] - '0') continue;
                    // cout << "I : " << fx[i] << " " << fy[i] << "\n";
                    if(fx[i] > fy[i]) {
                        unm = i;
                        break;
                    }
                }
                if(unm == -1 && tptr != 0){
                    //can we replace the current element?
                    // cout << "CHECK CURRENT\n";
                    for(int i = 0; i < 10; i++){
                        if(i <= y[tptr - 1] - '0') continue;
                        if(fx[i] > fy[i]) {
                            unm = i;
                            mptr = tptr - 1;
                            break;
                        }
                    }
                    auto incptr = inc.lower_bound(tptr - 1);
                    if(unm == -1 && incptr != inc.begin()){
                        //otherwise, have to look for first increase
                        // cout << "CHECK FIRST INC\n";
                        incptr --;
                        mptr = *incptr;
                        // cout << "WANT GREATER : " << y[mptr] << " " << mptr << endl;
                        for(int i = 0; i < 10; i++){
                            if(i <= y[mptr] - '0') continue;
                            // cout << fx[i] << " " << f[i].query(0, mptr) << endl;
                            if(fx[i] > f[i].query(0, mptr)) {
                                unm = i;
                                break;
                            }
                        }
                        // mptr --;
                    }   
                }
            }
            // cout << "MPTR UNM TPTR : " << mptr << " " << unm << " " << tptr << endl;
            //figure out answer
            int ans = -1;
            if(unm == -1){
                ans = -1;
            } 
            else if(ind < mptr) {
                ans = y[ind] - '0';
            }
            else if(ind == mptr){
                ans = unm;
            }
            else {  //ind > mptr
                vi cf = fx;
                for(int i = 0; i < 10; i++) cf[i] -= f[i].query(0, mptr);
                cf[unm] --;
                int diff = ind - mptr;
                for(int i = 0; i < 10; i++){
                    if(diff <= cf[i]) {
                        ans = i;
                        break;
                    }
                    diff -= cf[i];
                }
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}