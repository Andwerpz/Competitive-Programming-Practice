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

//Codeforces - 1993 F1, F2

//solved the easy version, have to study CRT more for the hard version. 

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

//modular inverse of a for any mod m. 
//if -1 is returned, then there is no solution. 
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

//solves the following system of congruences for x:
//x === a_1 % m_1
//x === a_2 % m_2
// ...
//x === a_n % m_n
//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
ll chinese_remainder_theorem(vector<ll> modulo, vector<ll> remainder) {
    assert(modulo.size() == remainder.size());
    ll M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    ll solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        ll a_i = remainder[i];
        ll M_i = M / modulo[i];
        ll N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll k;
        int n, w, h;
        cin >> n >> k >> w >> h;
        string s;
        cin >> s;
        w *= 2;
        h *= 2;
        pii pos = {0, 0};
        map<pii, ll> m;
        for(int i = 0; i < n; i++){
            if(s[i] == 'U'){
                pos.second ++;
            }
            else if(s[i] == 'D'){
                pos.second --;
            }
            else if(s[i] == 'L') {
                pos.first --;
            }
            else if(s[i] == 'R'){
                pos.first ++;
            }
            pos.first = (pos.first + w) % w;
            pos.second = (pos.second + h) % h;
            m[pos] ++;
        }
        pii inc = pos;
        ll px = w / gcd(w, inc.first);
        ll py = h / gcd(h, inc.second);
        ll period = (px * py) / gcd(px, py);
        cout << "INC : " << inc.first << " " << inc.second << "\n";
        cout << "PX PY : " << px << " " << py << "\n";
        cout << "PERIOD : " << period << "\n";
        ll ans = 0;
        for(auto i = m.begin(); i != m.end(); i++){
            ll amt = i->second;
            pii mv = i->first;
            pii loc = {-mv.first, -mv.second};
            loc.first = (loc.first + w) % w;
            loc.second = (loc.second + h) % h;
            //given k steps of inc, how many times do we visit loc?
            //i * inc.x = loc.x mod w
            //i * inc.y = loc.y mod h
            //i = loc.x / inc.x mod w
            //i = loc.y / inc.y mod h
            ll r1 = loc.first, r2 = loc.second;
            if(r1 % gcd(w, inc.first) != 0 || r2 % gcd(h, inc.second) != 0){
                //no solution possible, because it never actually goes to that coordinate. 
                continue;
            }
            ll m1 = w, m2 = h;
            ll a1 = inc.first, a2 = inc.second;
            //make it so that mod inv always exists for inc. 
            m1 /= gcd(w, inc.first);
            m2 /= gcd(h, inc.second);
            r1 /= gcd(w, inc.first);
            r2 /= gcd(h, inc.second);
            a1 /= gcd(w, inc.first);
            a2 /= gcd(h, inc.second);
            r1 = (r1 * mod_inv(a1, m1)) % m1;
            r2 = (r2 * mod_inv(a2, m2)) % m2;
            ll x = (chinese_remainder_theorem({m1, m2}, {r1, r2}) + period) % period;
            
            cout << "LOC : " << loc.first << " " << loc.second << "\n";
            cout << "CRT : " << m1 << " " << m2 << " " << r1 << " " << r2 << " " << x << "\n";

            ll cnt = 1 + (k - x) / period;
            ans += cnt * amt;
        }
        cout << ans << "\n";


        // pii inc = pos;
        // pos = {0, 0};
        // ll ans = 0;
        // for(int i = 0; i < k; i++){
        //     pii diff = {-pos.first, -pos.second};
        //     diff.first = (diff.first + w) % w;
        //     diff.second = (diff.second + h) % h;
        //     ans += m[diff];
        //     pos.first += inc.first;
        //     pos.second += inc.second;
        //     pos.first = (pos.first + w) % w;
        //     pos.second = (pos.second + h) % h;
        // }
        // cout << ans << "\n";
    }
    
    return 0;
}