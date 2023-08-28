#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1864E

//this one is kinda hard to explain, i solved it using mostly intuition. 

//the idea is that when alice or bob say 'i don't know', they are telling the other person something about the most significant bit. 

//note that if the most significant bit of a is less than a | b, then alice automatically knows that a < b. Likewise, in bobs case. 

//in the case where a and b share the most significant bit, it requires a back and forth between bob and alice before they can know for sure
//that they do. 

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
    if(b == 0){
        return 1;
    }
    ll ans = power(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
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

ll solve(vector<int>& a, bool init) {
    int msig = 0;
    //find the most significant bit
    for(int i = 0; i < a.size(); i++){
        int bit = 1;
        while(bit <= a[i]) {
            msig = max(msig, bit);
            bit *= 2;
        }
    }
    if(msig == 0){
        ll size = a.size();
        return mul(size, size);
    }
    vector<int> has(0);
    vector<int> not_has(0);
    for(int i = 0; i < a.size(); i++){
        if((a[i] & msig) == 0){
            not_has.push_back(a[i]);
        }
        else {
            has.push_back(a[i] - msig);
        }
    }
    ll ans = 0;
    //if other player has the higher significant bit
    ans = add(ans, mul(has.size(), not_has.size()));
    //if i have the higher significant bit
    ans = add(ans, mul(mul(has.size(), not_has.size()), 2));
    //if we both have the same significant bit
    ans = add(ans, mul(has.size(), has.size()));
    ans = add(ans, solve(has, false));
    //we both don't have the most significant bit
    ans = add(ans, solve(not_has, false));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll tot_games = mul(n, n);
        ll tot_moves = solve(a, true);
        //cout << tot_games << " " << tot_moves << "\n";
        cout << divide(tot_moves, tot_games) << "\n";
    }
    
    return 0;
}
