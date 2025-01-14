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

//Codeforces - 1427E

//basically just throwing stuff at the wall until it works. 
//the strategy i came up with is
// - first generate all powers of 2 multiples of x under 2^45
// - then randomly add together multiples to populate an xor basis. If you find a new basis vector, add it to the
//   list of potential adding stuff together
// - keep building the basis until 1 is included in the basis. 

//the intuition is that although an xor basis is a powerful way to create a specific element, adding will allow you to expand
//the xor basis. So by generating all powers of 2, we're giving a very large base of elements to generate the xor basis
//from. 

bool inBasis(vl& basis, ll x){
    for(int i = 0; i < basis.size(); i++)
        if(x & (1ll << i)) x ^= basis[i];
    return x == 0;
}

void insertBasis(vl& basis, ll x, vector<array<ll, 3>>& ops, set<ll>& s){
    if(inBasis(basis, x)) return;
    for(int i = 0; i < basis.size(); i++){
        if((x & (1ll << i)) == 0) continue;
        if(!basis[i]) {basis[i] = x; return;}
        x ^= basis[i];
        if(!s.count(x)) s.insert(x), ops.push_back({x ^ basis[i], 0, basis[i]});
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    int x;
    cin >> x;
    vector<array<ll, 3>> ops;  //{a, ? + : ^, b}
    vl b(45, 0), p(1, x);
    b[0] = x;
    set<ll> s;
    s.insert(x);
    while(true) {
        ll nx = p[p.size() - 1] * 2;
        if(nx >= (1ll << 45)) break;
        s.insert(nx);
        ops.push_back({nx / 2, 1, nx / 2});
        p.push_back(nx);
    }
    while(!inBasis(b, 1)) {
        ll u = p[rand() % p.size()], v = p[rand() % p.size()];
        ll op = 1;
        ll res = op? u + v : u ^ v;
        if(res >= (1ll << 45) || s.count(res)) continue;
        s.insert(res);
        ops.push_back({u, op, v});
        insertBasis(b, res, ops, s);
        p.push_back(res);
    }
    ll ptr = b[0];
    for(int i = 1; i < 45; i++){
        if(ptr & (1ll << i)) {
            ops.push_back({ptr, 0, b[i]});
            ptr ^= b[i];
        }
    }
    cout << ops.size() << "\n";
    for(int i = 0; i < ops.size(); i++){
        cout << ops[i][0] << " " << (ops[i][1]? "+" : "^") << " " << ops[i][2] << "\n";
    }
    
    return 0;
}