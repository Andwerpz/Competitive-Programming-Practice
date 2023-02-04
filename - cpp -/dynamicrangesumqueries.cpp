#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1648

//basic segtree problem

const int N = 1e6;  //limit for segtree size
int n;
ll t[2 * N];

void build() { // build the tree
    for (int i = n - 1; i > 0; i--) {   
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
}

ll query(int l, int r) { // sum on interval [l, r)
    ll res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res += (ll) t[l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res += (ll) t[r];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        modify(i, next);
    }
    while(q-- > 0){
        int t, a, b;
        cin >> t >> a >> b;
        if(t == 1){
            a--;
            modify(a, b);            
        }
        else {
            a--;
            cout << query(a, b) << "\n";
        }
    }
    
    return 0;
}
