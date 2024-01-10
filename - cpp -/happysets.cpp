#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//COMPFEST 15 H

//let's count the number of arrays where a[i] is a child of a[i + 1] for all valid i. We can permute
//these arrays to get the arrays the question is asking for. 

//the problem is that many of the arrays generated will have empty sets, and if we naively permute them,
//we'll overcount because empty sets are indistinguishable. Instead, we can fix the amount of 'full' sets, 
//by full, i just mean having at least 1 element. This way, we know exactly how to account for permutations. 

//before we count ways, let's first visualize the problem. Imagine the array of sets as a grid n wide
//and k tall. Each column corresponds to a set in the array, and each row represents one value from
//1 to k. An x in a column represents an element in that set. Below shows a possible valid array. 
//_| - - - - n - - - - |
//|  . . . . . . . . x  8
//|  . . . . . . . x .  7
//|  . . . . . . x . x  6
//k  . . . . . . . x x  5
//|  . . . . . . x x x  4
//|  . . . . . x . . x  3
//|  . . . . . . . x .  2
//_  . . . . . . x . x  1
//notice that wherever we place an x, we must also place one diagonally up and to the right. This continues 
//until we are at the last set. If putting an x requires putting another x above the grid, then that x can't
//be placed. 

//if we fix that 'f', f <= min(n, k), sets are full, what we're really doing is limiting how far left we can 
//place xs. But keep in mind that we still have to have 1 diagonal that is f xs long, because we are required to
//have f full sets. 

//we can split the diagonals into two categories, ones that can be f long, and ones that can't. With the ones
//that can't, computing the number of combinations is relatively easy; since there are no restrictions on these
//diagonals, we can just multiply the choices; 2 * 3 * 4 * ... * f = f!

//the diagonals that can be f long are harder, because there is a restriction that at least one of them be 
//be f long. We can reduce this to an array problem; we have an array of length k - (f - 1), each element can be
//an integer in the range [0, f], how many arrays have at least one element of value f? We can count the number of
//arrays that don't satisfy the condition, and subtract that from the total amount of arrays; (f + 1)^x - f^x
//where x is the length of the array. 

ll mod = 998244353;
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
    fac = vector<ll>(2e6, 1);
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
    
    fac_init();
    ll n, k;
    cin >> n >> k;
    ll ans = 1; //everything is the 0 set
    for(ll i = 1; i <= min(n, k); i++){
        //pick some subset to fix at i, then for the rest you can permute
        ll nr_i = k - (i - 1);
        ll ways = sub(power(i + 1, nr_i), power(i, nr_i));
        ways = mul(ways, fac[i]);   //corner
        ways = mul(ways, divide(fac[n], fac[n - i]));
        ans = add(ans, ways);
    }
    cout << ans << "\n";
    
    return 0;
}
