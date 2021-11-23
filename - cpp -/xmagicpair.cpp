
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1612D

//couldn't figure this one out

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll x, a, b;
        cin >> x >> a >> b;
        if(x == a || x == b){
            cout << "YES\n";
            continue;
        }
        ll min = std::min(a, b);
        ll max = std::max(a, b);
        min = std::min(min, max - min);
        if(x <= max && x % min == 0){
            cout << "YES\n";
            continue;
        }
        if(x <= min && (max + x) % min == 0){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
    
    return 0;
}
