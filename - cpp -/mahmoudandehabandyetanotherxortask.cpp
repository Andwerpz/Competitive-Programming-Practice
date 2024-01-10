#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 959F

//we can solve the queries offline. Sort the queries based on ascending value of l. Then, for each l, 
//we can check in constant time whether or not it's possible to make x using the first l elements. 

//to do this, we can maintain a set of basis vectors for each prefix. To see if an x is representable, we can
//just check if x can become another basis vector, if it can't then it's representable. If an x is not representable, 
//then there is no way to make it and the answer is 0. Otherwise, the answer is 2^(l - b) where b is the number
//of basis vectors, and l is the size of the prefix. 

ll mod = 1e9 + 7;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    ll ans = 1;
    ll p = a;
    while(b != 0){
        if(b % 2 == 1){
            ans = mul(ans, p);
        }
        p = mul(p, p);
        b /= 2;
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init() {
    fac = vector<ll>(1e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    ll ans = divide(fac[n], mul(fac[k], fac[sub(n, k)]));
    nckdp.insert({{n, k}, ans});
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<pair<int, pair<int, int>>> queries(q);   //{l, {x, i}}
    for(int i = 0; i < q; i++){
        cin >> queries[i].first;
        cin >> queries[i].second.first;
        queries[i].first --;
        queries[i].second.second = i;
    }
    sort(queries.begin(), queries.end());
    vector<ll> ans(q);
    vector<int> basis(20, -1);
    int nr_b = 0;
    int qptr = 0;
    for(int i = 0; i < n; i++){
        //add to basis
        int bvec = a[i];
        for(int j = 0; j < 20; j++){
            if((bvec & 1 << j) == 0){
                continue;
            }
            if(basis[j] == -1){
                basis[j] = bvec;
                nr_b ++;
                break;
            }
            bvec ^= basis[j];
        }
        //answer queries
        while(qptr != queries.size() && queries[qptr].first == i) {
            //check if we can add x to basis
            int x = queries[qptr].second.first;
            bool can_add = false;
            for(int j = 0; j < 20; j++){
                if((x & 1 << j) == 0) {
                    continue;
                }
                if(basis[j] == -1){
                    can_add = true;
                    break;
                }
                x ^= basis[j];
            }
            int ind = queries[qptr].second.second;
            ans[ind] = !can_add? power(2, i + 1 - nr_b) : 0;
            qptr ++;
        }
    }
    for(int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}
