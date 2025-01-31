#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
typedef unsigned int uint;
// typedef __int128 lll;
// typedef __float128 lld;

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
    
    uint ans = 0;
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    prime_sieve(10000);
    int prcnt = pr.size();
    for(int p : pr) {
        
    }
    for(int i = 10001; i <= n; i++){
        bool isprime = true;
        for(int p : pr) if(i % p == 0) {isprime = false; break;}
        if(!isprime) continue;
        prcnt ++;
    }
    cout << "PRCNT : " << prcnt << "\n";
    
    return 0;
}