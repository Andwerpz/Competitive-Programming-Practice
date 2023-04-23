#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range sum query, range assignment modify lazy seg tree

const int N = 16;
int t[2 * N];
int h = sizeof(int) * 8 - __builtin_clz(N); //height of tree
int d[N];   //lazy tree
int upd[N]; //upd[i] = true if t[i] needs to be updated

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
    if (p < N) {
        d[p] = value;
        upd[p] = true;
    }
}

void build(int l, int r) {
    l += N, r += N - 1;
    int k = 2; 
    for (; l > 1; k *= 2) {
        l /= 2, r /= 2;
        for (int i = r; i >= l; i--) {
            calc(i, k);
        }
    }
}

void push(int l, int r) {
    l += N, r += N - 1;
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
    for (l += N, r += N; l < r; l /= 2, r /= 2, k *= 2) {
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
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) res += t[l++];
        if (r % 2 == 1) res += t[--r];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    modify(3, 13, 1);
    query(6, 7);

    return 0;
}


