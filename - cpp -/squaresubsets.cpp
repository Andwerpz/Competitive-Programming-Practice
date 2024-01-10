#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 895C

//note that all the powers of the prime factors of a perfect square are even. 
//next, observe that the numbers are only in the range [1, 70]. There are 18 primes <= 70.

//this leads to a 2d bitset dp solution where
//dp[i][j] = nr ways to make given
//we've considered the first i elements in a
//the bits of j represent the parity of the powers in the number. 
//the answer at the end is dp[n][0]

//the problem is that j has to range in [0, 2^18), and since n = 10^5, this will take too long. 
//to optimize, we can once again take advantage of the fact that the numbers range from [1, 70].

//For each number in [1, 70], keep track of how many times it occurs. Then, when doing dp transitions, 
//note that picking any even sized subset will not change the parity of the powers, while picking an
//odd sized subset will change it as if you picked a single one. 

//All we have to do now is compute the number of ways to pick an even sized subset, and an odd sized one. 
//This can be done by looping through all sizes of subsets i, from 0 to s, where s is the amount of the current
//number, and computing s choose i.

vector<int> lp; //lowest prime factor 
vector<int> pr; //prime list

void prime_sieve(int n) {
    lp = vector<int>(n + 1);
    pr = vector<int>(0);
    for(int i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

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
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    ll ans = 1;
    ll p = a;
    while(b != 0){
        if(b % 2 == 1){
            ans = mul(ans, p);
        }
        p = mul(p, p);
        b /= 2;
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

void fac_init(int n = 2e6) {
    fac = vector<ll>(n, 1);
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

vector<int> find_prime_factors(int val) {
    vector<int> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve(100);
    fac_init(2e6);
    map<int, int> pr_bits;
    for(int i = 0; i < pr.size(); i++){
        pr_bits.insert({pr[i], i});
    }
    int n;
    cin >> n;
    map<int, ll> m;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        if(m.find(a) == m.end()) {
            m.insert({a, 0});
        }
        m[a] ++;
    }
    vector<ll> dp((1 << 20), 0);
    vector<ll> ndp((1 << 20), 0);
    dp[0] = 1;
    for(auto i = m.begin(); i != m.end(); i++){
        fill(ndp.begin(), ndp.end(), 0);
        int p_bits = 0;
        int val = i -> first;
        ll amt = i -> second;
        vector<int> f = find_prime_factors(val);
        for(int j = 0; j < f.size(); j++){
            p_bits ^= (1 << pr_bits[f[j]]);
        }
        ll nr_even = 0; //nr ways to pick an even and odd amount subset. 
        ll nr_odd = 0;
        for(int j = 0; j <= amt; j++){
            if(j % 2 == 0){
                nr_even = add(nr_even, nck(amt, j));
            }
            else {
                nr_odd = add(nr_odd, nck(amt, j));
            }
        }
        for(int j = 0; j < dp.size(); j++){
            //even
            ndp[j] = add(ndp[j], mul(dp[j], nr_even));
            //odd
            ndp[j ^ p_bits] = add(ndp[j ^ p_bits], mul(dp[j], nr_odd));
        }
        swap(dp, ndp);
    }
    cout << dp[0] - 1 << "\n";
    
    return 0;
}
