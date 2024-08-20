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

//AtCoder - ABC363F

//any number in the answer has to be a divisor of n, so we can first generate all the divisors of n. 
//since we cannot have any 0s, remove any divisor which has a 0. 

//Then, we want to identify any divisors that are palindromes, and divisors when reversed, also is a divisor
//of n. We can have one palindrome at the center of our answer, the rest of the numbers need to be
//reverse pairs of divisors. 

//since the number of divisor pairs is going to be small, we can just recursively try combinations of divisor
//pairs until the remainder a palindrome (at which point we've found the answer), or exhausted all combinations. 

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
    vector<ll> p(0), c(0);
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

bool calc_ans(set<ll>& pal_set, vector<pll>& r_set, int ind, ll val, vl& ans) {
    if(pal_set.count(val)) {
        //we're done
        ans.push_back(val);
        return true;
    }
    if(ind >= r_set.size()) {
        return false;
    }
    //search
    ll d = r_set[ind].first * r_set[ind].second;
    int cnt = 0;
    while(true) {
        if(calc_ans(pal_set, r_set, ind + 1, val, ans)) {
            for(int i = 0; i < cnt; i++){
                ans.push_back(r_set[ind].first);
                ans.insert(ans.begin(), r_set[ind].second);
            }
            return true;
        }
        if(val % d != 0){
            break;
        }
        cnt ++;
        val /= d;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n;
    cin >> n;
    prime_sieve(1e6 + 100);
    vl d = find_divisors(n);
    set<ll> dset;
    for(int i = 0; i < d.size(); i++){
        dset.insert(d[i]);
    }
    //find palindromes and reverse pairs
    set<ll> pal_set;
    vector<pll> r_set(0);
    for(int i = 0; i < d.size(); i++){
        string sd = to_string(d[i]);
        bool has_zero = false;
        for(int j = 0; j < sd.size(); j++){
            if(sd[j] == '0') {
                has_zero = true;
            }
        }
        if(has_zero){
            continue;
        }
        string rsd = sd;
        reverse(rsd.begin(), rsd.end());
        if(sd == rsd) {
            pal_set.insert(d[i]);
        }
        ll rd = stoll(rsd);
        if(d[i] != 1 && dset.count(rd) && rd >= d[i]) {
            r_set.push_back({d[i], rd});
        }
    }
    //gen ans
    vl ans(0);
    calc_ans(pal_set, r_set, 0, n, ans);
    if(ans.size() == 0){
        cout << "-1\n";
        return 0;
    }
    string sans = "";
    for(int i = 0; i < ans.size(); i++){
        sans += to_string(ans[i]);
        if(i != ans.size() - 1) {
            sans += "*";
        }
    }
    cout << sans << "\n";
    
    return 0;
}