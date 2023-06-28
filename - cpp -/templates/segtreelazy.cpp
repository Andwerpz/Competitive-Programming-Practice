#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range sum query, range assignment modify lazy seg tree

//start by modifying from 0 to n to 0.
struct SegtreeLazy {
    int n;
    int* t;
    int h;      //height of tree
    int* d;     //lazy tree
    int* upd;   //upd[i] = true if t[i] needs to be updated

    SegtreeLazy(int maxSize) {
        t = new int[maxSize * 2];
        h = sizeof(int) * 8 - __builtin_clz(maxSize);
        d = new int[maxSize];
        upd = new int[maxSize];
        n = maxSize;

        modify(0, maxSize, 0);
    }

    ~SegtreeLazy() {
        delete t;
        delete d;
        delete upd;
    }

    void calc(int p, int k) {   //accounting for length of segment 
        if (!upd[p]) {
            t[p] = t[p * 2] + t[p * 2 + 1];
        }
        else {
            t[p] = d[p] * k;
        }
    }

    void apply(int p, int value, int k) {
        t[p] = value * k;
        if (p < n) {
            d[p] = value;
            upd[p] = true;
        }
    }

    void build(int l, int r) {
        l += n, r += n - 1;
        int k = 2; 
        for (; l > 1; k *= 2) {
            l /= 2, r /= 2;
            for (int i = r; i >= l; i--) {
                calc(i, k);
            }
        }
    }

    void push(int l, int r) {
        l += n, r += n - 1;
        int s = h, k = 1 << (h - 1);
        for (; s > 0; s--, k /= 2) {
            for (int i = l >> s; i <= r >> s; i++) {
                if (upd[i]) {
                    apply(i * 2, d[i], k);
                    apply(i * 2 + 1, d[i], k);
                    d[i] = 0;
                    upd[i] = false;
                }
            }
        }
    }

    void modify(int l, int r, int value) {
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l /= 2, r /= 2, k *= 2) {
            if (l % 2 == 1) apply(l++, value, k);
            if (r % 2 == 1) apply(--r, value, k);
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);
    }

    int query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) res += t[l++];
            if (r % 2 == 1) res += t[--r];
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    SegtreeLazy segt(16);
    segt.modify(3, 13, 1);
    cout << segt.query(5, 15) << "\n";

    return 0;
}


