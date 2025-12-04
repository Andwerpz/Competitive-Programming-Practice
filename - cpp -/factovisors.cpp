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

//Kattis - factovisors

//bruh, they should really tell you how many testcases there are in the inputs. I looked, and the second sample
//has around 30 cases

//given that we know there are at most 30 cases, looping through all the primes under 5 * 10^4 is sufficient to not TLE

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

// - slow version, use when big number 
vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.push_back(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.push_back(val);
    }
    return factors;
}

// vector<ll> find_prime_factors(ll val) {
//     vector<ll> factors(0);
//     while(val != 1) {
//         factors.push_back(lp[val]);
//         val /= lp[val];
//     }
//     return factors;
// }

void find_divisors_helper(vector<ll>& p, vector<ll>& c, ll ind, ll val, vector<ll>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    find_divisors_helper(p, c, ind + 1, val, ans);
    for(ll i = 0; i < c[ind]; i++){
        val *= p[ind];
        find_divisors_helper(p, c, ind + 1, val, ans);
    }
}

//includes 1 as a divisor
vector<ll> find_divisors(ll val) {
    vector<ll> factors = find_prime_factors(val);
    map<ll, ll> m;
    vector<ll> p(0);
    vector<ll> c(0);
    for(ll i = 0; i < factors.size(); i++){
        ll next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        ll ind = m[next];
        c[ind] ++;
    }
    vector<ll> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ll cnt_fac_occ(ll n, ll f) {
    //compute how many times f will get contributed within n
    ll namt = 0, tmp = n;
    while(tmp != 0){
        namt += tmp / f;
        tmp /= f;
    }
    return namt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(5 * 1e4);
    // cout << "PCNT : " << pr.size() << "\n";
    ll n, m;
    cin >> n >> m;
    while(!cin.eof()) {
        bool is_valid = true;
        if(m == 0) is_valid = false;
        if(m <= n) {
            //do nothing
        }
        else {
            ll tmp = m;
            for(ll p : pr) {
                if(p > tmp) break;
                ll amt = 0;
                while(tmp % p == 0) amt ++, tmp /= p;
                ll namt = cnt_fac_occ(n, p);
                if(amt > namt) {
                    is_valid = false;
                    break;
                }
            }
            if(tmp != 1 && tmp > n) is_valid = false;
        }
        cout << m << (is_valid? " divides " : " does not divide ") << n << "!\n";
        cin >> n >> m;
    }
    
    return 0;
}