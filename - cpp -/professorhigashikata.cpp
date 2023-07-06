#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1847D

//first, determine for each character in s, what is it's first appearance in t(s). 
//we can do this using a set.
//order the characters in s based off of this.

//then, to maximize the lexicographical value, we simply want s to have the maximum prefix of 1s. 
//let tot = number of characters in s that appear in t(s).
//let nr1 = number of 1s in s. 
//then the amount of 1s in the prefix of s should be min(tot, nr1). 

//we can check how many 1s are already in the prefix using a range sum segment tree. 

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
    
    ll n, m, q;
    cin >> n >> m >> q;
    set<int> s;
    for(int i = 0; i < n; i++){
        s.insert(i);
    }
    string st;
    cin >> st;
    ll notused = 1e18;
    vector<ll> perm(n, notused);
    int ptr = 0;
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        l --;
        auto p = s.lower_bound(l);
        while(p != s.end() && *p < r) {
            perm[*p] = ptr ++;
            s.erase(p++);
        }
    }
    vector<ll> ind(n);
    for(ll i = 0; i < n; i++){
        ind[i] = i;
    }
    sort(ind.begin(), ind.end(), [&](ll a, ll b) -> bool {
        return perm[a] < perm[b];
    });
    ll tot = 0;
    for(ll i = 0; i < n; i++){
        if(perm[i] != notused){
            tot ++;
        }
    }
    ptr = 0;
    for(ll i = 0; i < n; i++){
        perm[ind[i]] = ptr ++;
    }
    Segtree tree = Segtree(1e6);
    tree.n = n;
    ll nr1 = 0;
    for(ll i = 0; i < n; i++){
        if(st[i] == '1'){
            nr1 ++;
            tree.modify(perm[i], 1);
        }
    }
    while(q--){
        ll x;
        cin >> x;
        x --;
        if(st[x] == '1'){
            nr1 --;
            st[x] = '0';
            tree.modify(perm[x], 0);
        }
        else {
            nr1 ++;
            st[x] = '1';          
            tree.modify(perm[x], 1);
        }
        ll ans = min(tot, nr1) - tree.query(0, min(tot, nr1));
        cout << ans << "\n";
    }

    return 0;
}
