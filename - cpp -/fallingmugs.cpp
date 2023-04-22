#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 C

//brute force all squares

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll d;
    cin >> d;
    map<ll, ll> s;
    bool found = false;
    for(ll i = 0; i <= 1e6; i++){
        ll sq = i * i;
        s.insert({sq, i});
        if(sq - d >= 0 && s.find(sq - d) != s.end()) {
            found = true;
            cout << s.find(sq - d) -> second << " " << i << "\n";
            break;
        }
    }
    if(!found) {
        cout << "impossible\n";
    }
    
    return 0;
}
