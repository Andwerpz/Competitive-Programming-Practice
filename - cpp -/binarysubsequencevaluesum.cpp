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

//Codeforces - 2077C

//this solution involves alot of looking at answers and guessing.

//first observe the following:
// - score of some v is solely determined by the difference between the number of 0s and 1s
// - let D = difference between nr 1s and nr 0s. Then, score is ceil(D / 2) * floor(D / 2)
// - fix D, how can we count the number of subsequences that have difference of D?
// - any subsequence that has difference D consists of a subsequence with difference 0, then D 0s or 1s

//I have A 0s and B 1s. How many subsequences of difference D do i have? 
//\sum_{i = 0}^{min(A, B - D)} \binom{A}{i} \binom{B}{i + D} + 
//\sum_{i = 0}^{min(A - D, B)} \binom{A}{i + D} \binom{B}{i}

//so taking the weighted sum of the above over all D will grant us the answer. We can then precompute some 
//answers as a function of A. Here is n = 6:
// 160 80 32 16 32 80 160

//actually, this looks suspiciously like a quadratic, and indeed if we compute the finite differences, we get
//a second order constant difference of 32. Actually in general, we'll see a second order difference of 2^n. 
//the first order differences actually also follow a stable pattern. 

//at this point, if we can just find the answer to some A, then we can derive all the other answers using the
//first and second order differences. It just so happens that if we plug in the sequence of answers for A = 0
//into OEIS, we get the sequence A001793 : a(n) = n*(n+3)*2^(n-3). 

//note that the actual implemented solution isn't this, I went and looked for the sequence to solve for the 
//actual quadratic. 

//can also observe that the number of subsequences with some fixed signed difference D is exactly \binom{n}{D + cnt0}
//where cnt0 is the number of 0s in the string and D is computed as D = c1 - c0 where c1 and c0 are the number of 
//1s and 0s in the subsequence. 

//this gives us this formula for the answer as a function of the number of 0s:
//a_cnt0 = \sum_{D = -cnt0}^{n - cnt0} \binom{n}{D + cnt0} ceil(D / 2) floor(D / 2)
//if we can quickly compute this for all cnt0 from 0 to n, then we can answer each query using a lookup. 

//we can actually quickly compute this using fft convolution. 
//define f_i = \binom{n}{i}, g_i = ceil(i / 2) floor(i / 2). Then a_i = \sum_{k = 0}^{n} f_k g_{k - i}
//we can make this exactly into a convolution by defining h_i = g_{-i}, then
//a_i = \sum_{k = 0}^{n} f_k h_{i - k}, so we just need to take convolution between f and h. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
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
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {return this->pow(mint(other));}

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

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//n >= k
mint nck(mint n, mint k) {
    // cout << "NCK : " << n << " " << k << endl;
    return fac[n] * invfac[k] * invfac[n - k];
}

int calc_f(vi& a) {
    int sfx = 0;
    for(int i = 0; i < a.size(); i++) sfx += a[i] == 1? 1 : -1;
    int pfx = 0, ans = 0;
    for(int i = 0; i < a.size(); i++) {
        pfx += a[i] == 1? 1 : -1;
        sfx -= a[i] == 1? 1 : -1;
        ans = max(ans, pfx * sfx);
    }
    return ans;
}

vi gen_bin(int n, int n0) {
    vi a(n, 1);
    for(int i = 0; i < n0; i++){
        while(true) {
            int ind = rand() % n;
            if(a[ind]) {a[ind] = 0; break;}
        }
    }
    return a;
}

//A001793 : a(n) = n*(n+3)*2^(n-3)
//equivalent to calc_ans(n, 0)
mint calc_b0(ll n) {
    if(n == 1) return 0;
    if(n == 2) return 1;
    if(n == 3) return 5;
    n --;
    return mint(n) * mint(n + 3) * mint(2).pow(n - 3);
}

mint calc_ans(ll a, ll b){
    mint ans = 0;
    //fix D
    for(int D = 0; D <= max(a, b); D++){
        mint sum = 0;
        for(int i = 0; i <= min(a, b - D); i++) sum += nck(a, i) * nck(b, i + D);
        for(int i = 0; i <= min(a - D, b); i++) sum += nck(a, i + D) * nck(b, i);
        ans += sum * (D / 2) * ((D + 1) / 2);
    }
    return ans;
}

namespace fft {
    const double PI = acos(-1);

    void fft(vector<complex<double>>& a) {
        int n = a.size(), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<complex<double>> rt(2, 1);  // (^ 10% faster if double)
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n);
            rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for (int i = k; i < 2 * k; i++) 
                rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
        }
        vector<int> rev(n);
        for (int i = 0; i < n; i++) 
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; i++) 
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2) 
            for (int i = 0; i < n; i += 2 * k) 
                for (int j = 0; j < k; j++) {
                    // complex<double> z = rt[j + k] * a[i + j + k]; // (25% faster if hand-rolled)  /// include-line
                    auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];  /// exclude-line
                    complex<double> z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }

    vector<double> conv(const vector<double>& a, const vector<double>& b) {
        if (a.empty() || b.empty()) return {};
        vector<double> res(a.size() + b.size() - 1);
        int L = 32 - __builtin_clz(res.size()), n = 1 << L;
        vector<complex<double>> in(n), out(n);
        copy(a.begin(), a.end(), in.begin());
        for (int i = 0; i < b.size(); i++) 
            in[i].imag(b[i]);
        fft(in);
        for (complex<double>& x : in) 
            x *= x;
        for (int i = 0; i < n; i++) 
            out[i] = in[-i & (n - 1)] - conj(in[i]);
        fft(out);
        for (int i = 0; i < res.size(); i++) 
            res[i] = imag(out[i]) / (4 * n);
        return res;
    }

    template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
        if (a.empty() || b.empty()) return {};
        vector<ll> res(a.size() + b.size() - 1);
        int B = 32 - __builtin_clz(res.size()), n = 1 << B, cut = int(sqrt(M));
        vector<complex<double>> L(n), R(n), outs(n), outl(n);
        for (int i = 0; i < a.size(); i++) 
            L[i] = complex<double>((int)a[i] / cut, (int)a[i] % cut);
        for (int i = 0; i < b.size(); i++) 
            R[i] = complex<double>((int)b[i] / cut, (int)b[i] % cut);
        fft(L), fft(R);
        for (int i = 0; i < n; i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl), fft(outs);
        for (int i = 0; i < res.size(); i++) {
            ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
            ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    //precompute for n, all the answers
    vm ans(n + 1, 0);
    if(false) { //guessforces
        if(n == 1) ans = {0, 0};
        else if(n == 2) ans = {1, 0, 1};
        else if(n == 3) ans = {5, 1, 1, 5};
        else {
            //ans[i] = ai^2 + bi + c
            mint a = mint(2).pow(n - 2);
            mint b = -mint(n + 2) * mint(2).pow(n - 2);
            mint c = (mint(n - 1) * mint(n - 1) + mint(7) * (n - 1) + 8) * mint(2).pow((n - 1) - 3);
            // cout << "EQN : " << a << " " << b * -1 << " " << c << "\n";
            for(int i = 0; i <= n; i++){
                ans[i] = a * mint(i + 1) * mint(i + 1) + b * mint(i + 1) + c;
            }
        }
    }
    else {  //convolution
        vl f(n + 1), h(2 * n + 1);
        for(int i = 0; i <= n; i++) f[i] = nck(n, i).val;
        for(int i = 0; i <= 2 * n; i++) {
            ll D = abs(n - i);
            h[i] = (mint(D / 2) * mint((D + 1) / 2)).val;
        }
        vl c = fft::convMod<mod>(f, h);
        for(int i = 0; i <= n; i++) ans[i] = c[i + n];

        // for(ll D = 0; D <= n; D++) ans[0] += nck(n, D) * ((D * D - abs(D) % 2) / 4);
        // for(int c0 = 0; c0 <= n / 2; c0++){
        //     for(ll D = -c0; D <= n - c0; D++){
        //         ans[c0] += nck(n, D + c0) * ((D * D - abs(D) % 2) / 4);
        //     }
        // }
    }
    // cout << "ANSS :\n";
    // for(int i = 0; i <= n; i++) {
    //     cout << "A : " << i << " " << ans[i] << "\n";
    // }
    string s;
    cin >> s;
    int a = 0;
    for(int i = 0; i < n; i++) a += s[i] == '1';
    while(q--){
        int i;
        cin >> i;
        i --;
        a -= s[i] == '1';
        s[i] = s[i] == '1'? '0' : '1';
        a += s[i] == '1';
        cout << ans[a] << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // int n = 5;
    // for(int n0 = 0; n0 <= n; n0++){
    //     set<int> s;
    //     for(int i = 0; i < 100; i++){
    //         vi a = gen_bin(n, n0);
    //         s.insert(calc_f(a));
    //     }
    //     cout << "N0 : " << n0 << " ABS DIFF : " << abs((n - n0) - n0) << "\n";
    //     for(int x : s) cout << x << " ";
    //     cout << "\n";
    // }

    fac_init(1e6);

    // for(int x = 10; x >= 0; x--){
    //     for(int i = 1; i < 10; i++) {
    //         if(x > i) cout << "0 ";
    //         else cout << calc_ans(i - x, x) << " ";
    //     }
    //     cout << "\n";
    // }
    // for(int i = 1; i < 10; i++) cout << calc_b0(i) << " ";
    // cout << "\n";
    // for(int i = 1; i < 10; i++){
    //     for(int a = 0; a <= i; a++) cout << calc_ans(a, i - a) << " ";
    //     cout << "\n";
    // }

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    
    return 0;
}