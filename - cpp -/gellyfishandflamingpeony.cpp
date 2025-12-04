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

//Codeforces - 2115A

//bruh, didn't expect bitset dp to be intended. 

//first, all the elements are going to eventually become the minimum possible element, which is equal to the
//gcd of all the elements in the array. 

//if there already exists some element equal to the minimum, we can simply use this element to gcd with all others
//otherwise, we need to create the minimum possible element in the minimum amount of moves. 

//first, we can divide all elements by the gcd, now we just want to create a '1'. Then, we can do some sort of 
//bitset dp to find for each element, the minimum amount of other elements we must gcd into it to become equal to 1.
//Since each element has at most 5 unique prime factors, this just has a complexity of O(n * 32), which is good enough. 

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
// vector<ll> find_prime_factors(ll val) {
//     vector<ll> factors(0);
//     for(int i = 0; i < pr.size(); i++){
//         while(val % pr[i] == 0){
//             factors.push_back(pr[i]);
//             val /= pr[i];
//         }
//     }
//     if(val != 1){
//         factors.push_back(val);
//     }
//     return factors;
// }

vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(10000);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int ming = 0;
        for(int i = 0; i < n; i++) ming = gcd(ming, a[i]);
        int mingcnt = 0;
        for(int i = 0; i < n; i++) if(a[i] == ming) mingcnt ++;
        if(mingcnt != 0) {
            cout << n - mingcnt << "\n";
            continue;
        }
        //otherwise, need to pick some element to become equal to ming
        for(int i = 0; i < n; i++) a[i] /= ming;
        ming = 1;
        int ans = 2 * n;
        for(int i = 0; i < n; i++){
            map<int, int> f;
            vl pf = find_prime_factors(a[i]);
            for(ll x : pf) f[(int) x] ++;
            vi of(0);
            for(auto j = f.begin(); j != f.end(); j++) {
                int p = j->first, occ = j->second;
                of.push_back(p);
            }
            //what's the minimum amount of elements to gcd together to get this guy to minimum
            //do dp
            int m = of.size();
            vi dp((1 << m), 1e9);
            dp[0] = 0;
            vi trans((1 << m), 0);
            //precalc all transitions
            for(int j = 0; j < n; j++){
                int ct = 0;
                for(int k = 0; k < m; k++) if(a[j] % of[k] != 0) ct += (1 << k);
                trans[ct] = true;
            }
            for(int j = 0; j < (1 << m); j++){
                //try all transitions
                for(int k = 0; k < (1 << m); k++){
                    if(trans[k]) dp[j | k] = min(dp[j | k], dp[j] + 1);
                }
            }
            // cout << "PICK " << i << " : " << dp[(1 << m) - 1] << "\n";
            // for(int x : of) cout << x << " ";
            // cout << "\n";
            ans = min(ans, dp[(1 << m) - 1] + n - 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}