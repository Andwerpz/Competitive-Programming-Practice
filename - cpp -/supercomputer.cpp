#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 04 B

//classic range sum segtree problem

const int N = 2e6;  //limit for segtree size
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> n >> k;
    while(k-- > 0){
        string type;
        cin >> type;
        if(type == "F"){
            int ind;
            cin >> ind;
            ind --;
            modify(ind, t[ind + n] ^ 1);
        }
        else if(type == "C"){
            int l, r;
            cin >> l >> r;
            cout << query(--l, r) << "\n";
        }
    }
    
    return 0;
}
