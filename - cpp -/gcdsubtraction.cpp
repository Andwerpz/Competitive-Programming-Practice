#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC159B

//we can first simulate the problem, then optimize. 

//note that the gcd between a and b only increases as we apply operations. 

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
    for(ll i = 0; i <= c[ind]; i++){
        find_divisors_helper(p, c, ind + 1, val, ans);
        val *= p[ind];
    }
}

vector<ll> find_divisors(ll val) {
    vector<ll> factors = find_prime_factors(val);
    //cout << "found prime factors : " << val << endl;
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

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve(1e6 * 2);
    ll a, b;
    cin >> a >> b;
    if(a > b){
        swap(a, b);
    }
    if(a == b){
        cout << "1\n";
        return 0;
    }
    ll ans = 0;
    while(a != 0){
        //cout << "A B : " << a << " " << b << endl;
        ll g = gcd(a, b);
        a /= g;
        b /= g;
        
        //subtract increment should now be 1
        ll diff = b - a;
        if(diff == 1){
            ans += a;
            break;
        }
        //find when we'll change to the next gcd
        vector<ll> div = find_divisors(diff);
        //cout << "found divisors" << endl;
        ll ca = 0;
        for(int i = 0; i < div.size(); i++){
            ll d = div[i];
            if(d == 1){
                continue;
            }
            ll nca = a - (a % d);
            ca = max(ca, nca);
        }
        ll sub = a - ca;
        ans += sub;
        a -= sub;
        b -= sub;
    }
    cout << ans << "\n";
    
    return 0;
}
