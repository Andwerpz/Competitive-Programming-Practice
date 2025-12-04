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

//Meta Hacker Cup 2025 Round 1 - B1 B2

//for B1, you can just defer all work until the last day. Since A >= 1, this will always work.

//for B2, we can observe that to count sequences, we can just arrange put the prime factors of B
//into the 2N days, and any unique arrangement of prime factors will yield a unique sequence. 

//next, observe that B has at most around 53 prime factors. So probably a brute force backtracking
//solution is sufficient. 

//for each unique prime factor, we can iterate across all ways to distribute it between the two halves.
//to count the number of ways to place prime factors within a half, we reduce it to counting
//lattice paths. 

const ll N = 100000000;
ll lp[N + 1];
vector<ll> pr;

void prime_sieve() {
    for(ll i = 2; i <= N; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= N; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

// - slow version, use when big number 
vector<ll> find_prime_factors(ll val) {
    // cout << "FIND FACTORS : " << val << endl;
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

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 7;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod); val %= mod;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    bool operator >(const mint& other) const {return val > other.val;}
    bool operator >(ll other) const {return val > other;}
    bool operator <(const mint& other) const {return val < other.val;}
    bool operator <(ll other) const {return val < other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {return *this + mint(other);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {return *this - mint(other);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return *this * mint(other);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return *this * other.pow(mod - 2);}
    mint operator /(ll other) const {return *this / mint(other);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return *this % mint(other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}

    //don't forget about fermat's little theorem, 
    //a^(m-1) % m = 1. This means that a^(p % m) % m != a^(p) % m, rather a^(p % (m-1)) % m = a^(p) % m. 
    mint pow(ll b) const {
        mint ans(1), p(val);
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return mint(a) == b;}
bool operator !=(ll a, const mint& b) {return mint(a) != b;}
bool operator >(ll a, const mint& b) {return mint(a) > b;}
bool operator <(ll a, const mint& b) {return mint(a) < b;}
mint operator +(ll a, const mint& b) {return mint(a) + b;}
mint operator -(ll a, const mint& b) {return mint(a) - b;}
mint operator *(ll a, const mint& b) {return mint(a) * b;}
mint operator /(ll a, const mint& b) {return mint(a) / b;}
mint operator %(ll a, const mint& b) {return mint(a) % b;}

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//k small, n huge
vm lat;
mint lattice(ll n, ll k) {
    //need to compute n + k choose k
    mint ans = invfac[k];
    for(int i = 0; i < k; i++) {
        ans *= mint(n + k - i);
    }
    return ans;
}

//n >= k
mint nck(mint n, mint k) {
    return fac[n] * invfac[k] * invfac[n - k];
}

ll n, a, b;

mint solve(vector<pll>& ff, int ind, ll lprod, mint amt) {
    // cout << "SOLVE : " << ind << endl;
    if(ff.size() == ind) return amt;
    ll p = ff[ind].first;
    ll pamt = ff[ind].second;
    assert(pamt != 0);
    mint ans = 0;
    for(int i = 0; i <= pamt; i++) {
        if(lprod > a) break;
        ans += solve(ff, ind + 1, lprod, amt * lat[i] * lat[pamt - i]);
        lprod *= p;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("final_product_chapter_2_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    prime_sieve();
    fac_init(1000);

    // cout << "DONE SIEVE" << endl;

    const int MAXP = 55;
    // const int MAXN = 10;
    // vvm dp = vvm(MAXN + 1, vm(MAXP + 1, 0));  
    // dp[0][0] = 1;
    // for(int i = 0; i < MAXN; i++) {
    //     for(int j = 0; j <= MAXP; j++) {
    //         if(j != 0) dp[i + 1][j] += dp[i + 1][j - 1];
    //         dp[i + 1][j] += dp[i][j];
    //     }

    //     // for(int k = 0; k <= MAXP; k++) {
    //     //     for(int j = 0; j <= k; j++) {
    //     //         dp[i + 1][k] += dp[i][j];
    //     //     }
    //     // }
    // }

    // for(int i = 0; i <= MAXN; i++) {
    //     for(int j = 0; j <= MAXP; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    // for(int i = 0; i <= MAXN; i++) {
    //     for(int j = 0; j <= MAXP; j++) {
    //         if(i == 0) cout << "0 ";
    //         else cout << lattice(i - 1, j) << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "DONE DP" << endl;

    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        cin >> n >> a >> b;

        lat = vm(MAXP + 1);
        for(int i = 0; i <= MAXP; i++) lat[i] = lattice(n - 1, i);
        vl factors = find_prime_factors(b);
        map<ll, ll> freq;
        for(ll f : factors) freq[f] ++;
        vector<pll> ff(0);  //{prime, freq}
        for(auto i = freq.begin(); i != freq.end(); i++) {
            ff.push_back({i->first, i->second});
            // cout << "FF : " << i->first << " " << i->second << "\n";
        }
        mint ans = solve(ff, 0, 1, 1);
        cout << "Case #" << casi << ": " << ans << "\n";

        // cout << "Case #" << casi << ": ";
        // for(int i = 0; i < 2 * n - 1; i++) cout << "1 ";
        // cout << b << "\n";
    }
    
    return 0;
}