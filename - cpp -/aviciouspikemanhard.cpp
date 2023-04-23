#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 13 E

//look for loops. Since each t_i is less than or equal to c, we know that there can be maximum c values before a loop 
//starts. 

//once we know how many of each problem time there are, we can just simulate from there. 

ll mod = 1e9 + 7;

ll pow(ll a, ll b){
    if(b == 0){
        return 1;
    }
    ll ans = pow(a, b / 2);
    ans *= ans;
    ans %= mod;
    if(b % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

ll divide(ll a, ll b) {
    return (a * pow(b, mod - 2)) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll t;
    cin >> t;
    ll a, b, c;
    cin >> a >> b >> c;
    vector<ll> time(c + 1, 0);
    ll pt;
    cin >> pt;
    vector<int> l(0);
    set<int> s;
    while(true){
        l.push_back(pt);
        s.insert(pt);
        pt = (pt * a + b) % c + 1;
        if(s.find(pt) != s.end()){
            break;
        }
        if(s.size() == n){
            break;
        }
    }
    if(s.size() == n){
        for(int i = 0; i < n; i++){
            time[l[i]] ++;
        }
    }
    else {
        vector<int> loop(0);
        bool foundLoop = false;
        for(int i = 0; i < l.size(); i++){
            if(l[i] == pt) {
                foundLoop = true;
            }
            if(foundLoop) {
                loop.push_back(l[i]);
            }
            else {
                n --;
                time[l[i]] ++;
            }
        }
        ll loops = n / loop.size();
        for(int i = 0; i < loop.size(); i++){
            time[loop[i]] += loops;
            if(i < n % loop.size()) {
                time[loop[i]] ++;
            }
        }
    }
    ll curTime = 0;
    ll nsolve = 0;
    ll penalty = 0;
    for(ll i = 1; i <= c; i++){
        ll np = min((t - curTime) / i, time[i]);
        //cout << "PROBME : " << i << " " << np << "\n";
        nsolve += np;
        penalty += (np * (curTime % mod)) % mod;
        if(penalty >= mod){
            penalty -= mod;
        }
        penalty += ((((np * (np + 1)) / 2) % mod) * i) % mod;
        if(penalty >= mod){
            penalty -= mod;
        }
        curTime += np * i;
    }
    cout << nsolve << " " << penalty << "\n";
    
    return 0;
}
