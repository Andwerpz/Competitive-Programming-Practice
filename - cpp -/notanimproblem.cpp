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

//Codeforces - 2004E

//since this is a nim problem (the title is a lie D:), if we can quickly compute the grundy number for each
//pile, then we can outright solve the problem. 

//g[0] = 0, and g[1] = 1. Next, g[even] = 0. We get this via induction due to the fact that if a[i] is even,
//then we can't subtract an even number from it, it must go to an odd number, and that all odd numbers
//must be able to go to at least one even number (by subtracting 1). So we also get g[odd] > 0. 

//now, note that g[prime] is just g[prev(prime)] + 1, where prev(prime) is the largest prime
//smaller than prime. This is because some prime is coprime to all numbers below it. 
//(of course, g[2] is still 0, g[3] = 2)

//finally, odd composite numbers. Define lp[x] as the lowest prime factor of x. For any odd composite number x, 
//i say that g[x] = g[lp[x]]. I can remove any amount of stones y from x if y < lp[x], and within the range
//(x - lp[x], x), all primes less than lp[x] will have a multiple. This means that g[x] must be at least
//g[prev(lp[x])] + 1. Finally, note that x cannot travel to any number z where lp[x] = lp[z], as 
//gcd(x, z - x) != 1. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    prime_sieve(1e7 + 100);
    map<int, int> pr_mp;
    for(int i = 1; i < pr.size(); i++){
        pr_mp[pr[i]] = i + 1;
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        int g = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] % 2 == 0){
                continue;
            }
            if(a[i] == 1){
                g ^= 1;
                continue;
            }
            g ^= pr_mp[lp[a[i]]];
        }
        cout << (g == 0? "Bob" : "Alice") << "\n";
    }
    
    return 0;
}