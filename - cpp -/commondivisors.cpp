#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1081

//as a rule of thumb, the maximum number of divisors in the range [0, n] is around n^(1/3). 
//so for this problem, we assume the number of divisors for each x is around 100. 

//for each number in the array, we generate all of its divisors. 
//we can keep track of how many times each divisor appears, and if a divisor appears twice or more, then it
//must have come from two different numbers. 

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
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
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
    vector<int> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve(2 * 1e6);
    int n;
    cin >> n;
    vector<int> cnt(1e6 + 100, 0);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        vector<int> d = find_divisors(next);
        for(int i = 0; i < d.size(); i++){
            cnt[d[i]] ++;
        }
    }
    int ans = 1;
    for(int i = 0; i < cnt.size(); i++){
        if(cnt[i] >= 2){
            ans = i;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
