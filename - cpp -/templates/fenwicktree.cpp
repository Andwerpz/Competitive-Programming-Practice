#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//point update, range query
template <typename T>
struct FTPR {
    int n;
    T* a;

    FTPR(int _n) {
        n = _n;
        a = new T[n];
        for(int i = 0; i < n; i++) a[i] = 0;
    }

    //returns the sum in range [0, r)
    T sum(int r) {
        r --;
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += a[r];
        return ret;
    }

    //returns the sum in range [l, r)
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void add(int ind, T val) {
        for (; ind < n; ind = ind | (ind + 1))
            a[ind] += val;
    }
};

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

//range update, range query
template <typename T>
struct FTRR {
    int n;
    T *a1, *a2;

    FTRR(int _n) {
        n = _n;
        a1 = new T[n + 1];
        a2 = new T[n + 1];
        for(int i = 0; i < n; i++) {
            a1[i] = 0;
            a2[i] = 0;
        }
    }
    
    void _add(T* a, int ind, T val) {
        ind ++;
        while(ind <= n) {
            a[ind] += val;
            ind += ind & -ind;
        }
    }

    //sum in range [0, ind)
    T _sum(T* a, int ind) {
        T ans = 0;
        while(ind > 0) {
            ans += a[ind];
            ind -= ind & -ind;
        }
        return ans;
    }

    void add(int l, int r, T val) {
        _add(a1, l, val);
        _add(a1, r, -val);
        _add(a2, l, val * l);
        _add(a2, r, -val * r);
    }

    T pref_sum(int ind) {
        return _sum(a1, ind) * ind - _sum(a2, ind);
    }

    T sum(int l, int r) {
        return pref_sum(r) - pref_sum(l);
    }

    void add(int ind, T val) {
        add(ind, ind + 1, val);
    }

    T sum(int ind) {
        return sum(ind, ind + 1);
    }
};