#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//COMPFEST 15 B

//lcm(a, b) = (a * b) / gcd(a, b) -> lcm(a, b) * gcd(a, b) = (a * b)
//if we take x := lcm(a, b) and y := gcd(a, b), then x * y = a * b. 

//this is only true though, if gcd(a * b) = y. When taking the gcd of two numbers, we can
//go through each of the prime factors, and take the minimum power between the two numbers for that factor. 
//the resulting number is the gcd. 

//thus, we just have to count how many ways we can rearrange the prime factors of x * y such that the minimum
//for each prime factor equals the count in y. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<ll, ll> f;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    int m;
    cin >> m;
    vector<ll> c(m), d(m);
    for(int i = 0; i < m; i++){
        cin >> c[i];
    }
    for(int i = 0; i < m; i++){
        cin >> d[i];
    }
    for(int i = 0; i < n; i++){
        if(f.find(a[i]) == f.end()) {
            f.insert({a[i], 0});
        }
        f[a[i]] += b[i];
    }
    for(int i = 0; i < m; i++){
        if(f.find(c[i]) == f.end()) {
            f.insert({c[i], 0});
        }
        f[c[i]] += d[i];
    }
    map<ll, ll> g;
    for(int i = 0; i < m; i++){
        if(g.find(c[i]) == g.end()) {
            g.insert({c[i], 0});
        }
        g[c[i]] += d[i];
    }
    for(auto i = f.begin(); i != f.end(); i++){
        ll factor = i -> first;
        if(g.find(factor) == g.end()){
            g.insert({factor, 0});
        }
    }
    ll ans = 1;
    ll mod = 998244353;
    for(auto i = f.begin(); i != f.end(); i++){
        ll factor = i -> first;
        ll gcd = g[factor];
        ll amt = f[factor];
        if(gcd * 2 > amt) {
            ans *= 0;
            break;
        }
        if(gcd * 2 < amt){
            ans *= 2;
            ans %= mod;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
