#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 04 H

//just check the bits in n - 1. 

//n - 1 because the empty set is set 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n;
    cin >> n;
    while(n != 0){
        n --;
        ll pow = 1;
        vector<ll> ans(0);
        //cout << "{ ";
        while(n != 0){
            if(n % 2 == 1){
                //cout << pow << ", ";
                
            }
            pow *= 3;
            n /= 2;
        }
        //cout << "}\n";
        cin >> n;
    }
    
    return 0;
}
