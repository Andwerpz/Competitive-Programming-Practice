#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1806E

//time complexity is O(n * sqrt(n)) assuming O(1) operations for the map, but it seems the constant factor of the map 
//is too large, so it tle. 

vector<int> w;
vector<int> p;
unordered_map<int, ll> cache[200001];

ll solve(int a, int b) {
    if(a == -1){
        return 0;
    }
    if(a > b){
        swap(a, b);
    }
    if(cache[a].count(b)) {
        return cache[a][b];
    }
    ll ans = 1ll * w[a] * w[b] + solve(p[a], p[b]);
    cache[a][b] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    w = vector<int>(n);
    p = vector<int>(n, -1);
    for(int i = 0; i < n; i++){
        cin >> w[i];
    }
    for(int i = 1; i < n; i++){
        cin >> p[i];
        p[i] --;
    }
    while(q-- != 0){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        cout << solve(a, b) << "\n";
    }
    
    return 0;
}

// https://codeforces.com/contest/1806/submission/198019367

// #include <cstdio>
// #include <cstring>
// #include <iostream>
// #include <unordered_map>
// #include <vector>
// using namespace std;
// typedef long long ll;
// const int base = 1e8 + 7;
// struct hash_map {
//     int head[base];
//     vector<int> next;
//     vector<ll> key;
//     vector<ll> val;
//     hash_map() { memset(head, -1, sizeof(head)); }
//     int hash(ll k) { return k % base; }
//     ll &operator[](ll k) {
//     int h = hash(k);
//     for (int i = head[h]; ~i; i = next[i])
//         if (key[i] == k) return val[i];
//     next.push_back(head[h]);
//     key.push_back(k);
//     val.push_back(0);
//     head[h] = next.size() - 1;
//     return val.back();
//     }
//     ll has_key(ll k) {
//     int h = hash(k);
//     for (int i = head[h]; ~i; i = next[i])
//         if (key[i] == k) return true;
//     return false;
//     }
// };
// hash_map val;
// ll get_val(vector<ll> &a, vector<int> &f, int u, int v) {
//     if (!u) return 0;
//     if (u > v) swap(u, v);
//     ll id = u;
//     id = id << 32 | v;
//     if (val.has_key(id)) return val[id];
//     return val[id] = get_val(a, f, f[u], f[v]) + a[u] * a[v];
// }
// int main() {
//     ios::sync_with_stdio(false);
//     int n, q;
//     cin >> n >> q;
//     vector<ll> a(n + 1);
//     for (int i = 1; i <= n; i++) cin >> a[i];
//     vector<int> f(n + 1);
//     for (int i = 2; i <= n; i++) cin >> f[i];
//     while (q--) {
//     int u, v;
//     cin >> u >> v;
//     cout << get_val(a, f, u, v) << endl;
//     }
//     return 0;
// }
