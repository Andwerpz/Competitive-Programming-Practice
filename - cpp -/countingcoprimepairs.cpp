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

//CSES - 2417

//we can count the number of non-coprime pairs, and then subtract from the total amount
//of pairs. 

//for each prime, count the number of pairs that include that prime. This will naturally
//double count pairs which share two prime factors, so exclude all pairs which share two primes. 
//This will exclude all pairs which share 3 primes, and so on. In general, we want to include
//all odd numbered factors, and exclude even numbers. 

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

void gen_pr(vi& ans, ll cpr, int sind, int iter) {
    if(iter == -1){
        ans.push_back(cpr);
        return;
    }
    for(int i = sind; i < pr.size(); i++){
        if(cpr * pr[i] > 1e6) {
            return;
        }
        gen_pr(ans, cpr * pr[i], i + 1, iter - 1);
    }   
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6);
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vl f(1e6 + 1, 0);
    for(int i = 0; i < n; i++){
        f[a[i]] ++;
    }
    ll ans = 0;
    for(int i = 0; i < 20; i++){
        vi c(0);
        gen_pr(c, 1, 0, i);
        for(int j = 0; j < c.size(); j++){
            int val = c[j];
            ll csum = 0;
            for(int k = val; k < f.size(); k += val) {
                csum += f[k];
            }
            ans += csum * (csum - 1) / 2 * (i % 2? -1 : 1);
        }
    }
    ans = (ll) n * (n - 1) / 2 - ans;
    cout << ans << "\n";
    
    return 0;
}