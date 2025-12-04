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

//Kattis - jumpingchoreography
//BAPC 2017 - J

//make sure to not misread the problem, the number of modifications that can be done is 10^6, it's just that
//you can only add/remove frogs 5000 times. 

//so the number of frogs is relatively small, and actually the range of positions is also relatively small. 
//this hints at a solution where you do alot of work every time you add/remove a frog, so that you can easily
//query the total cost of placing a tower anywhere. 

//first, lets try to compute the minimum number of jumps required for a frog to move +-d positions. 
//actually, we don't need to use DP to compute this, if you simulate the DP naively, you'll notice that it's possible
//to get to some offset +-d in S moves if d is the same parity as S * (S + 1) / 2 and d <= S * (S + 1) / 2

//next, observe that there are at most around sqrt(10^6) unique costs. This means that if we have some range update
//datastructure, we can update the costs when adding/removing some frog in sqrt(10^6) operations, and query
//the cost of a tower very quickly

//since parity is annoying, it's best to consider even and odd parity tower positions separately. 
//also, actually implementing the cost increments is very annoying. 

const int MAXT = 1e6 + 100;
// const int MAXT = 1000;

//range update, point query
template <typename T>
struct FTRP {
    int n;
    T* a;

    FTRP(int _n) {
        n = _n;
        a = new T[n];
        for(int i = 0; i < n; i++) a[i] = 0;
    }

    //returns a[ind]
    T sum(int ind) {
        T ret = 0;
        for (; ind >= 0; ind = (ind & (ind + 1)) - 1)
            ret += a[ind];
        return ret;
    }

    void add(int ind, T val) {
        for (; ind < n; ind = ind | (ind + 1))
            a[ind] += val;
    }

    //adds val to range [l, r)
    void add(int l, int r, T val) {
        add(l, val);
        add(r, -val);
    }
};

vl calc_dist() {
    vl dist(MAXT, 1e9);
    dist[0] = 0;
    {
        int eptr = 0;
        int esptr = 0;
        int optr = 0;
        int osptr = 0;
        for(int i = 1; i < MAXT; i++) {
            if(i % 2) {
                while(osptr < i || (osptr % 2) == 0) {
                    optr ++;
                    osptr += optr;
                }
                dist[i] = optr;
            }
            else {
                while(esptr < i || (esptr % 2) == 1) {
                    eptr ++;
                    esptr += eptr;
                }
                dist[i] = eptr;
            }
        }
    }
    return dist;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vl dist = calc_dist();
    FTRP<int> oft(MAXT), eft(MAXT);
    auto upd_even = [](int pos, int sign, FTRP<int>& ft) -> void {
        int psum = 0;
        int sum = 0;
        for(int i = 1; psum < MAXT; i++) {
            sum += i;
            ft.add(0, max(0, pos - psum), sign);
            ft.add(min(MAXT, pos + psum + 1), MAXT, sign);
            if(sum % 2 == 0) {
                psum = sum;
            }
        }
    };
    auto upd_odd = [](int pos, int sign, FTRP<int>& ft) -> void {
        int psum = 0;
        int sum = 0;
        for(int i = 1; psum < MAXT; i++) {
            sum += i;
            ft.add(0, max(0, pos - psum), sign);
            ft.add(min(MAXT, pos + psum + 1), MAXT, sign);
            if(sum % 2 == 1) {
                psum = sum;
            }
        }
    };
    auto upd_ft = [&](int pos, int sign) -> void {
        if(pos % 2 == 0) {
            upd_even(pos, sign, eft);
            upd_odd(pos, sign, oft);
        }
        else {
            upd_even(pos, sign, oft);
            upd_odd(pos, sign, eft);
        }
    };  
    int n, t;
    cin >> n >> t;
    for(int i = 0; i < n; i++){
        int p;
        cin >> p;
        upd_ft(p, 1);
    }
    int c;
    cin >> c;
    for(int i = 0; i < c; i++) {
        string type;
        int a;
        cin >> type >> a;
        if(type == "t") {
            t = a;
        }
        else if(type == "+") {
            upd_ft(a, 1);
        }
        else if(type == "-") {
            upd_ft(a, -1);
        }
        ll ans;
        if(t % 2 == 0) ans = eft.sum(t);
        else ans = oft.sum(t);
        cout << ans << "\n";
    }
    
    return 0;
}