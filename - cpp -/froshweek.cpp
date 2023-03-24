#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 F

//the amount of swaps required for a given value is simply the amount of values before it that are greater than it. 

//either normalize the values and use segtree, or use an ordered set

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
    
    cin >> n;
    vector<int> a(n);
    //normalize
    vector<int> o(n);
    map<int, int> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        o[i] = a[i];
    }
    sort(o.begin(), o.end());
    for(int i = 0; i < n; i++){
        m.insert({o[i], i});
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        a[i] = m.find(a[i]) -> second;
        ans += query(a[i], n);
        modify(a[i], 1);
    }
    cout << ans << "\n";

    return 0;
}
