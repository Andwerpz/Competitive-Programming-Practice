#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
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

//2024 ICPC NAQ - J

//can test if coordinate is not in current level of sponge, and then recurse downwards. 

//going to higher level is literally multiplying by 3, and then modulo 1, so the rational
//numbers will never explode. 

bool leq(pll a, pll b) {
    pll _a = {a.first * b.second, a.second * b.second};
    pll _b = {b.first * a.second, a.second * b.second};
    return _a.first <= _b.first;
}

bool le(pll a, pll b){
    pll _a = {a.first * b.second, a.second * b.second};
    pll _b = {b.first * a.second, a.second * b.second};
    return _a.first < _b.first;
}

bool geq(pll a, pll b){
    pll _a = {a.first * b.second, a.second * b.second};
    pll _b = {b.first * a.second, a.second * b.second};
    return _a.first >= _b.first;
}

bool ge(pll a, pll b){
    pll _a = {a.first * b.second, a.second * b.second};
    pll _b = {b.first * a.second, a.second * b.second};
    return _a.first > _b.first;
}

bool out_sponge(pll x) {
    return ge(x, {1, 3}) && le(x, {2, 3});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int l;
    cin >> l;
    pll x, y, z;
    cin >> x.first >> x.second >> y.first >> y.second >> z.first >> z.second;
    for(int i = 0; i < l; i++){
        // cout << "XYZ : " << x.first << " " << y.first << " " << z.first << "\n";
        if((out_sponge(x) && out_sponge(y)) || (out_sponge(y) && out_sponge(z)) || (out_sponge(x) && out_sponge(z))) {
            cout << "0\n";
            return 0;
        }
        x.first = (x.first * 3) % x.second;
        y.first = (y.first * 3) % y.second;
        z.first = (z.first * 3) % z.second;
    }
    cout << "1\n";
    
    return 0;
}