#include <vector>
#include <iostream>
#include <algorithm>
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

//POJ - 3904

//lets count the number of ordered coprime quadruples, and then subtract out the bad ones (some quadruples can 
//duplicate two elements, or they can be different orderings of the same 4 elements) to find the answer. 

//The number of ordered coprime quadruples can be found using the mobius inversion. I won't go through 
//the derivation, but the result turns out to be \sum_{d = 1} m(d) * (# of x, d | x)^4, where m is the mobius function. 

//Now, we need to subtract out the bad ones. We can subtract out all the coprime single elements (which is just the amount
//of 1s), 14x the coprime pairs (14x because each coprime pair is counted that many times), 36x the triples, and divide the
//remainder by 24 (because each coprime quadruple is ordered 4! ways) to get the final answer. 

//we can compute the amount of coprime pairs and triples in much the same way, and that is left as an exercise to the reader. 

ll binexp(ll a, ll b) {
    ll p = a;
    ll ans = 1;
    while(b != 0){
        if(b % 2) ans *= p;
        p *= p;
        b /= 2;
    }
    return ans;
}

vector<ll> mobius;
void calc_mobius(int n) {
    mobius = vector<ll>(n + 1, 0);
    mobius[1] = 1;
    vector<bool> c(n + 1, false);
    vector<ll> p(0);
    for(int i = 2; i <= n; i++){
        if(!c[i]) {
            p.push_back(i);
            mobius[i] = -1;
        }
        for(int j = 0; j < p.size() && i * p[j] <= n; j++){
            c[i * p[j]] = true;
            if(i % p[j] == 0){
                mobius[i * p[j]] = 0;
                break;
            }
            else {
                mobius[i * p[j]] = mobius[i] * mobius[p[j]];
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_mobius(1e5);
    int n;
    cin >> n;
    while(!cin.eof()) {
        vl f(10005, 0);
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            f[a] ++;
        }
        ll ca = 0, cb = 0, cc = 0, cd = 0;
        for(int d = 1; d < f.size(); d++){
            ll amt = 0;
            for(int j = d; j < f.size(); j += d) {
                amt += f[j];
            }
            ca += amt * mobius[d];
            cb += amt * amt * mobius[d];
            cc += amt * amt * amt * mobius[d];
            cd += amt * amt * amt * amt * mobius[d];
        }
        ll ansa = ca;
        ll ansb = (cb - ansa) / 2;
        ll ansc = (cc - ansa - ansb * 6) / 6;
        ll ansd = (cd - ansa - ansb * 14 - ansc * 36) / 24;
        cout << ansd << "\n";
        cin >> n;
    }
    
    return 0;
}