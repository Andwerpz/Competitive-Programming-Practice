#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2013 - D

//given the number of prime factors of a number k, where p[i] denotes the amount of the ith prime factor,
//the number of permutations is (p[0] + p[1] + ... + p[n])! / (p[0]! * p[1]! * ... * p[n]!)

//note that since we are only concerned with the minimum k for a given value f(k), we always want to
//order the primes in ascending order; 2 will always have more than or equal occurrences than 3, and so on. 

//the main observation is that there doesn't exist many k where k < 2^63 and f(k) < 2^63, mainly because
//k will rapidly grow beyond 2^63. Then, the idea is to brute force all possible k where k < 2^63.

//be careful of overflows. With c++, you can just use __int128. 

lll limit = ((lll) 1 << 63);
map<lll, lll> m;    //map each possible n to lowest k. 

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

void pre_calc(int max_nr, int pr_ind, lll nr_prime, lll nr_perm, lll val) {
    lll cur_pr = pr[pr_ind];
    for(int i = 0; i < max_nr; i++){
        val *= cur_pr;
        if(val >= limit) {
            return;
        }
        nr_prime ++;
        nr_perm *= nr_prime;
        nr_perm /= (i + 1);
        if(nr_perm >= limit) {
            return;
        }
        if(m.find(nr_perm) == m.end()) {
            m.insert({nr_perm, val});
        }
        m[nr_perm] = min(m[nr_perm], val);
        pre_calc(i + 1, pr_ind + 1, nr_prime, nr_perm, val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    prime_sieve(1e5);
    m = map<lll, lll>();
    m.insert({1, 2});
    pre_calc(70, 0, 0, 1, 1);
    ll n;
    cin >> n;
    while(!cin.eof() && n != 0) {
        cout << n << " " << (ll) m[n] << "\n";
        cin >> n;
    }
    
    return 0;
}
