#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1822G1 / G2

//the only difference between the easy and hard version is the range on a[i]. In the easy version, a[i] <= 10^6, 
//while in the hard version, a[i] <= 10^9. 
//It pretty much just tests whether or not you can factor numbers up to 10^9 quickly.

//since they don't specify an ordering for the triples, (i, j, k), we can first sort the array. 

//for each value, a[i], we want to find all of the divisors 'd' such that d^2 also divides a[i].
//then, we just check how many times a[i] / d and a[i] / d^2 occur in the array, and construct triples from those occurrences. 

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

vector<int> find_prime_factors(int val) {
    vector<int> factors(0);
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

void find_divisors_helper(vector<int>& p, vector<int>& c, int ind, int val, vector<int>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    for(int i = 0; i <= c[ind]; i++){
        find_divisors_helper(p, c, ind + 1, val, ans);
        val *= p[ind];
    }
}

//actually finds all divisors 'd', such that d^2 also divides val. 
vector<int> find_divisors(int val) {
    vector<int> factors = find_prime_factors(val);
    map<int, int> m;
    vector<int> p(0);
    vector<int> c(0);
    for(int i = 0; i < factors.size(); i++){
        int next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        int ind = m[next];
        c[ind] ++;
    }
    for(int i = 0; i < c.size(); i++){
        c[i] /= 2;
    }
    vector<int> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve((int) sqrt(1e9) + 1);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll ans = 0;
        map<int, ll> m;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(m.find(next) == m.end()) {
                m.insert({next, 0ll});
            }
            m.find(next) -> second ++;
        }
        for(auto i = m.begin(); i != m.end(); i++){
            int next = i -> first;
            vector<int> d = find_divisors(next);
            if(i -> second >= 3){
                ans += i -> second * (i -> second - 1) * (i -> second - 2);
            }
            for(int j = 1; j < d.size(); j++){  //skip divisor '1'
                int a = next / (d[j] * d[j]);
                int b = next / d[j];
                if(m.find(a) != m.end() && m.find(b) != m.end()) {
                    //cout << next << " " << b << " " << a << "\n";
                    ans += m.find(next) -> second * m.find(a) -> second * m.find(b) -> second;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
