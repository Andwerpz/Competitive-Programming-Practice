#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 C

//implementation. 

ll gcd(ll a, ll b) {
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a * b) / gcd(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        ll greater = 0;
        ll less = 1e9;
        ll lc = 1;
        for(int i = 0; i < n; i++){
            string type;
            cin >> type;
            string tmp;
            ll next;
            cin >> tmp >> next;
            if(type == "less") {
                less = min(less, next);
            }
            if(type == "greater") {
                greater = max(greater, next);
            }
            if(type == "divisible") {
                lc = lcm(lc, next);
            }
        }
        ll rem = (((greater) % lc) + lc) % lc;
        ll next = (greater) + (lc - rem);
        if(lc == 1){
            next = greater + 1;
        }
        if(greater == -1 || less == 1e9) {
            cout << "infinite\n";
        }
        else if(next >= less) {
            cout << "none\n";
        }
        else {
            for(ll i = next; i < less; i += lc) {
                cout << i << " ";
            }
            cout << "\n";
        }
        cin >> n;
    }
    
    return 0;
}
