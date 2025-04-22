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

//solves ax + by = gcd(a, b) for (x, y)
ll euclid(ll a, ll b, ll &x, ll &y) {
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    const int N = 1e5;
    vl pr(0);
    vb isprime(N + 1, true);
    for(int i = 2; i <= N; i++){
        if(isprime[i]) {
            pr.push_back(i);
            for(int j = i * 2; j <= N; j += i) {
                isprime[j] = false;
            }
        }
    }
    cout << "DONE PRIMES" << endl;

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 1) {
            cout << "1/1\n";
            continue;
        }
        if(n == 2) {
            cout << "1/2\n";
            continue;
        }
        vl p(0);
        for(int i = 0; i < pr.size(); i++){
            if(pr[i] > n) break;
            ll cur = 1;
            while(cur * pr[i] <= n) cur *= pr[i];
            cout << "CUR : " << cur << endl;
            p.push_back(cur);
        }
        int m = p.size();
        sort(p.begin(), p.end());
        cout << "M : " << m << endl;
        vl c(m, -1);
        //work backwards
        ll tgt = 1;
        for(int i = m - 2; i >= 0; i--){
            ll a = p[i + 1];
            ll b = 1;
            for(int j = 0; j <= i; j++){
                // b = (b * p[j]) % a;
                b = b * p[j];
            }
            ll x, y;
            euclid(a, b, x, y);
            x *= tgt, y *= tgt;
            cout << "EUCLID : " << a << "*" << x << " + " << b << "*" << y << " = " << tgt << "\n";
            c[i + 1] = y;
            tgt = x;
        }
        c[0] = tgt;
        cout << "C : ";
        for(int i = 0; i < m; i++) cout << c[i] << " ";
        cout << "\n";
        cout << "P : ";
        for(int i = 0; i < m; i++) cout << p[i] << " ";
        cout << "\n";
        for(int i = 0; i < m; i++){
            if(c[i] < 0) cout << "-";
            if(c[i] > 0 && i != 0) cout << "+";
            cout << abs(c[i]) << "/" << p[i];
        }
        cout << "\n";
    }

    return 0;
}