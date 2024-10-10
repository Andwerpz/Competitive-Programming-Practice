#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Calgary 2022 - H

//just compute the complex inverse of b. 

pld mult(pld a, pld b){
    return {a.first * b.first - a.second * b.second, a.first * b.second + a.second * b.first};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    pld a, b;
    cin >> a.first >> a.second >> b.first >> b.second;
    pld c = {b.first / (b.first * b.first + b.second * b.second), -b.second / (b.first * b.first + b.second * b.second)};
    a = mult(a, c);
    cout << fixed << setprecision(10) << a.first << " " << a.second << "\n";
    
    return 0;
}