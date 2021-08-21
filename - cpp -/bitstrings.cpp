
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Bitstrings

int main() {
    
    int n;
    cin >> n;
    ll mod = 1e9 + 7;
    ll ans = 1;
    for(int i = 0; i < n; i++){
        ans *= 2;
        ans %= mod;
    }
    cout << ans;

    return 0;
}



