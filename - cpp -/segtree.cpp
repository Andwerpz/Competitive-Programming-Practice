#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range sum query, single assignment modify seg tree

//note that t[0] is not used
const int N = 1e5;  //limit for segtree size
int n;
int t[2 * N];

void build() { // build the tree
    for (int i = n - 1; i > 0; i--) {   
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (; p > 0; p /= 2) {
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
}

int query(int l, int r) { // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res += t[l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res += t[r];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){ //input values into tree
        cin >> t[i + n];
    }
    build();
    
    return 0;
}
