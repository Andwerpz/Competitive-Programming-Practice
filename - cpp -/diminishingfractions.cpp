#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//2024 ICPC Polish Collegiate Programming Contest - D

//first, observe that the lower bound on the answer is 1 / lcm(1, 2, ..., n). The LCM from 1 to n is also given by
//\prod p_i^{k_i}, where p_i are unique primes under n and k_i is the largest positive integer such that p_i^{k_i} <= n. 

//so we have c_1 / p_1^{k_1} + c_2 / p_2^{k_2} + \cdots = 1 / M, where M is the lcm. Multiplying both sides by M we get
//c_1 M / p_1^{k_1} + \cdots = 1
//Now, lets say that we only require the left side to be congruent to 1 mod M. We'll figure out a way to subtract out the
//integer portion later. So we have
//c_1 M / p_1^{k_1} + \cdots === 1 (mod M)
//observe that if we replace the mod with p_1^{k_1}, it drops all the other terms on the left side except for c_1, and we get
//c_1 M / p_1^{k_1} === 1 (mod p_1^{k_1})
//we can do this for every i, giving us a nice formula for c_i:
//c_i === (M / p_i^{k_i})^{-1} (mod p_i^{k_i})
//now to subtract out the integer portion, we can evaluate these fractions in floating point and round to the nearest integer.
//since 1 / M will get very small very fast, it's sufficient to just round to the nearest integer. 

//in order to not TLE, you also have to do some optimizations, but you can look at the code to figure those out. 
//(you can't process the queries online. If you increment n, then you can easily update the answer using the previous answer)

ll binpow(ll a, ll b, ll mod) {
    ll pow = a, ans = 1;
    while(b != 0){
        if(b % 2) ans = (ans * pow) % mod;
        pow = (pow * pow) % mod;
        b /= 2;
    }
    return ans;
}

//assumes mod is prime, or at least is relatively prime to a. 
ll modinv(ll a, ll mod) {
    return binpow(a, mod - 2, mod);
}

//computes a^{-1} mod p^k where p is prime, p^k is relatively small, a and p are coprime
ll modinv(ll a, ll p, ll k) {  
    ll pk = binpow(p, k, 1e9 + 7);
    ll totient = pk - pk / p;
    return binpow(a, totient - 1, pk);
}

//solves ax + by = gcd(a, b) for (x, y)
ll euclid(ll a, ll b, ll &x, ll &y) {
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    const int N = 5 * 1e4;
    // const int N = 10;
    vl pr(0);
    vb isprime(N + 1, true);
    vl lp(N + 1, -1);
    for(int i = 2; i <= N; i++){
        if(isprime[i]) {
            lp[i] = i;
            pr.push_back(i);
            for(int j = i * 2; j <= N; j += i) {
                isprime[j] = false;
                if(lp[j] == -1) lp[j] = i;
            }
        }
    }
    vb ispowp(N + 1, false);
    for(int i = 2; i <= N; i++){
        ll cp = lp[i], cur = i;
        while(cur % cp == 0) cur /= cp;
        if(cur == 1) ispowp[i] = true;
        // cout << "CUR : " << cur << " " << i << endl;
    }
    vi prind(N + 1, -1);
    for(int i = 0; i < pr.size(); i++) {
        prind[pr[i]] = i;
    }

    int t;
    cin >> t;
    vector<int> ns(t);
    for(int i = 0; i < t; i++) cin >> ns[i];
    vb hast(N + 1, false);
    for(int i = 0; i < t; i++) hast[ns[i]] = true;
    vector<string> anss(N + 1, "");
    anss[1] = "1/1";
    vl p(0), k(0), pk(0), c(0);
    for(int n = 2; n <= N; n++){
        int m = p.size();
        if(ispowp[n]) {
            //update c. c[i] = (M / pk[i])^{-1} % pk[i]
            //so just have to completely recalculate the one that got updated, and then update the rest
            ll cp = lp[n];
            ll ind = prind[cp];
            if(ind >= p.size()) {
                p.push_back(cp);
                k.push_back(1);
                pk.push_back(cp);
                c.push_back(-1);
                m ++;
            }
            else {
                k[ind] ++;
                pk[ind] = n;
            }
            {
                ll cur = 1;
                for(int i = 0; i < m; i++) if(i != ind) cur = (cur * pk[i]) % pk[ind];
                cur = modinv(cur, p[ind], k[ind]);
                c[ind] = cur;
            }
            for(int i = 0; i < m; i++){
                if(i == ind) continue;
                c[i] = (c[i] * modinv(p[ind], p[i], k[i])) % pk[i];
            }
        }
        if(hast[n]) {
            //construct ans string
            ll off;
            {
                ld tmp = 0;
                for(int i = 0; i < m; i++) tmp += (ld) c[i] / (ld) pk[i];
                off = -(ll) (abs(round(tmp - 0.0001)) + 0.0001);
            }
            anss[n] += to_string(off) + "/1";
            for(int i = 0; i < m; i++) anss[n] += "+" + to_string(c[i]) + "/" + to_string(pk[i]);
            if(n == 2) anss[n] = "1/2";
        }
    }   
    for(int i = 0; i < t; i++) cout << anss[ns[i]] << "\n";

    // int t;
    // cin >> t;
    // while(t--){
    //     int n;
    //     cin >> n;
    //     if(n == 1) {
    //         cout << "1/1\n";
    //         continue;
    //     }
    //     if(n == 2) {
    //         cout << "1/2\n";
    //         continue;
    //     }
    //     vl p(0), k(0), pk(0);
    //     for(int i = 0; i < pr.size(); i++){
    //         if(pr[i] > n) break;
    //         ll cur = 1, ck = 0;
    //         while(cur * pr[i] <= n) cur *= pr[i], ck ++;
    //         // cout << "CUR : " << cur << endl;
    //         p.push_back(pr[i]);
    //         k.push_back(ck);
    //         pk.push_back(cur);
    //     }
    //     int m = p.size();
    //     vl c(m);
    //     for(int i = 0; i < m; i++){
    //         ll cur = 1;
    //         for(int j = 0; j < m; j++) if(i != j) cur = (cur * pk[j]) % pk[i];
    //         cur = modinv(cur, p[i], k[i]);
    //         c[i] = cur;
    //     }
    //     ll off;
    //     {
    //         ld tmp = 0;
    //         for(int i = 0; i < m; i++) tmp += (ld) c[i] / (ld) pk[i];
    //         // cout << "TMP : " << fixed << setprecision(10) << tmp << endl;
    //         off = -(ll) (abs(round(tmp)) + 0.0001);
    //     }
    //     cout << off << "/1";
    //     for(int i = 0; i < m; i++){
    //         cout << "+" << c[i] << "/" << pk[i];
    //     }
    //     cout << "\n";
    // }

    return 0;
}