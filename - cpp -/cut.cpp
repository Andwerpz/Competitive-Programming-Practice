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

//Codeforces - 1516D

//nice binary lifting problem. 

//to find the minimum partition of an array, we can use a greedy strategy: repeatedly partition off
//the largest prefix where all pairwise GCDs are 1, and that will give us the minimum amount of partitions. 

//to quickly answer queries, we first want to compute for each index l, what's the maximum subarray [l, r) such
//that all the elements are coprime. We can do this quickly (n * log(n)) if we factorize all elements of the array,
//and keep track of what was the last time we've seen each prime factor. 

//then to answer queries, we can do binary lifting on the thing we generated in the previous step. 

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
    set<ll> s;
    vector<ll> factors(0);
    while(val != 1) {
        s.insert(lp[val]);
        val /= lp[val];
    }
    for(ll x : s){
        factors.push_back(x);
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e5 + 5);
    int n, q;
    cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vi lsp(1e5 + 5, n), c(n + 1, n);
    for(int i = n - 1; i >= 0; i--){    
        vl f = find_prime_factors(a[i]);
        for(int x : f){
            c[i] = min(c[i], lsp[x]);
            lsp[x] = i;
        }
        c[i] = min(c[i], c[i + 1]);
    }
    vvi bit(n + 1, vi(20));
    for(int i = 0; i < n; i++){
        bit[i][0] = c[i];
    }
    bit[n] = vi(20, n);
    for(int b = 1; b < 20; b++){
        for(int i = n - 1; i >= 0; i--){
            bit[i][b] = bit[bit[i][b - 1]][b - 1];
        }
    }
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l --;
        int ans = 1;
        for(int b = bit[0].size() - 1; b >= 0; b--){
            if(bit[l][b] < r){
                ans += (1 << b);
                l = bit[l][b];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}