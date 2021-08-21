
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Trailing Zeroes

int main() {
    
    int n;
    cin >> n;
    int ans = 0;
    ll power = 5;
    while(power <= n){
        ans += n / power;
        power *= 5;
    }
    cout << ans;

    return 0;
}



