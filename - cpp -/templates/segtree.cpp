#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//range sum query, single assignment modify seg tree
struct Segtree {
    //note that t[0] is not used
    int n;
    int* t;

    Segtree(int maxSize) {
        t = new int[2 * maxSize];

        for(int i = 0; i < 2 * maxSize; i++){
            t[i] = 0;
        }
    }

    ~Segtree() {
        delete t;
    }

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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    Segtree tree(1e6);
    for(int i = 0; i < n; i++){ 
        cin >> tree.t[i + n];   //input values into tree
    }
    tree.build();
    
    return 0;
}
