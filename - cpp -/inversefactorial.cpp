#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 13 B

//if a % m = b % m, then it's a (m - 1) / m chance that a = b. 

//if you do this with multiple m; a % m_0 = b % m_0, a % m_1 = b % m_1, etc, then you multiply these probabilities. 

//you can mod the large number given in linear time, then do a search over all factorials. 

//since the large number has at most 10^6 digits, you only have to search to around 10^6 factorial. 

ll mod_arr(vector<int> a, ll mod) {
    ll ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans *= 10;
        ans += a[i];
        ans %= mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string num;
    cin >> num;
    vector<int> a(num.size(), 0);
    for(int i = 0; i < num.size(); i++){
        a[i] = num[i] - '0';
    }
    vector<ll> mod = {(ll) 1e9 + 7, (ll) 1e9 + 9, (ll) 1e9 + 21, (ll) 1e9 + 33};
    vector<ll> rem(mod.size());
    for(int i = 0; i < mod.size(); i++){
        rem[i] = mod_arr(a, mod[i]);
    }
    vector<ll> remT(mod.size(), 1);
    ll ptr = 1;
    while(true) {
        bool isValid = true;
        for(int i = 0; i < remT.size(); i++){
            if(remT[i] != rem[i]){
                isValid = false;
                break;
            }
        }
        if(isValid) {
            break;
        }
        ptr ++;
        for(int i = 0; i < remT.size(); i++){
            remT[i] = (remT[i] * ptr) % mod[i];
        }
    }
    cout << ptr << "\n";
    
    return 0;
}
