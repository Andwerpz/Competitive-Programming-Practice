#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - seti

//this problem can be reduced into solving a system of linear equations. 

//each letter f(k) is equivalent to the summation
//a[0] * k^0 + a[1] * k[1] + ... + a[n - 1] * k^(n - 1)
//under the mod p. 

//we can then generate n such equivalences, and use gaussian elimination to solve for a[i]. 

ll mod = 1e9 + 7;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    if(ans >= mod) {
        ans %= mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = power(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init() {
    fac = vector<ll>(1e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    ll ans = divide(fac[n], mul(fac[k], fac[sub(n, k)]));
    nckdp.insert({{n, k}, ans});
    return ans;
}

ll catalan(ll n){
    return sub(nck(2 * n, n), nck(2 * n, n + 1));
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
ll cantor(ll a, ll b, ll m) {
    return ((a + b) * (a + b + 1) / 2 + b) % m;
}

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

//modular inverse of a for any mod m. 
//if -1 is returned, then there is no solution. 
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
ll chinese_remainder_theorem(vector<ll>& modulo, vector<ll>& remainder) {
    if(modulo.size() != remainder.size()) {
        return -1;
    }
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

vector<int> soln;

void solve(vector<vector<int>> coeff, vector<int> const_val) {
    if(coeff.size() == 1){
        soln.insert(soln.begin(), divide(const_val[0], coeff[0][0]));
        return;
    }
    //take the first coeff and solve for it. 
    vector<int> coeff_soln(coeff.size() - 1);
    int const_val_soln = divide(const_val[0], coeff[0][0]);
    for(int i = 0; i < coeff_soln.size(); i++){
        coeff_soln[i] = divide(sub(mod, coeff[0][i + 1]), coeff[0][0]);
    }
    //create new system of equations and find solution
    vector<vector<int>> n_coeff(coeff.size() - 1, vector<int>(coeff.size() - 1, 0));
    for(int i = 0; i < n_coeff.size(); i++){
        for(int j = 0; j < n_coeff.size(); j++){
            n_coeff[i][j] = add(coeff[i + 1][j + 1], mul(coeff_soln[j], coeff[i + 1][0]));
        }
    }
    vector<int> n_const_val(const_val.size() - 1, 0);
    for(int i = 0; i < n_const_val.size(); i++){
        n_const_val[i] = sub(const_val[i + 1], mul(const_val_soln, coeff[i + 1][0]));
    }
    solve(n_coeff, n_const_val);
    //compute solution
    int cur_soln = const_val_soln;
    for(int i = 0; i < soln.size(); i++){
        cur_soln = add(cur_soln, mul(soln[i], coeff_soln[i]));
    }
    soln.insert(soln.begin(), cur_soln);
    return;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        cin >> mod;
        string s;
        cin >> s;
        int n = s.size();
        vector<int> const_val(s.size());
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '*') {
                const_val[i] = 0;
            }
            else {
                const_val[i] = s[i] - 'a' + 1;
            }
        }
        vector<vector<int>> coeff(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                coeff[i][j] = power(i + 1, j);
            }
        }
        soln.clear();
        solve(coeff, const_val);
        for(int i = 0; i < soln.size(); i++){
            cout << soln[i] << " \n"[i == soln.size() - 1];
        }
        // cout << "REVERSE : ";
        // for(int i = 1; i <= n; i++){
        //     int val = 0;
        //     for(int j = 0; j < n; j++){
        //         val = add(val, mul(soln[j], pow(i, j)));
        //     }
        //     if(val == 0){
        //         cout << " ";
        //     }
        //     else {
        //         cout << (char) (val - 1 + 'a');
        //     }
        // }
        // cout << "\n";
    }
    
    return 0;
}
