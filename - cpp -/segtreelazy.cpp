#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range sum query, range assignment modify lazy seg tree

const int N = 1e5;  //segtree size
int t[2 * N];
int h = sizeof(int) * 8 - __builtin_clz(N); //height of tree
int d[N];   //lazy tree

//k is the length of the segment

void calc(int p, int k) {   //accounting for length of segment 
    if (d[p] == 0) t[p] = t[p * 2] + t[p * 2 + 1];
    else t[p] = d[p] * k;
}

void apply(int p, int value, int k) {
    t[p] = value * k;
    if (p < N) d[p] = value;
}

void build(int l, int r) {
    l += N, r += N - 1;
    int k = 2;  //build goes bottom to top, so we initialize k to 2; we don't calculate anything for the leaves but start with their direct parents
    for (; l > 1; k *= 2) {
        l /= 2, r /= 2;
        for (int i = r; i >= l; i--) {
            calc(i, k);
        }
    }
}

void push(int l, int r) {
    l += N, r += N - 1;
    int s = h, k = 1 << (h - 1);    //push goes top to bottom, so k's initial value depends here on the height of the tree and is divided by 2 on each level.
    for (; s > 0; s--, k /= 2) {
        for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
            apply(i * 2, d[i], k);
            apply(i * 2 + 1, d[i], k);
            d[i] = 0;
        }
    }
}

void modify(int l, int r, int value) {
    if (value == 0) return;
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
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        modify(i, i + 1, next);
    }
    cout << query(5, n) << "\n";
    
    return 0;
}


