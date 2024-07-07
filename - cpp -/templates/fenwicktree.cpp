#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    T* a;

    FenwickTree(int _n) {
        n = _n;
        a = new T[n];
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