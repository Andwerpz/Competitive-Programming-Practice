
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1612D

//a gcd based solution

//first, make it so that a >= b. 

//then, if b > a - b, then b = a - b.


bool solve(ll a, ll b, ll x){
    if(a == x || b == x){
        return true;
    }
    if(b > a){
        swap(a, b);
    }
    if (b > a - b){
       b = a - b; 
    } 
    if (x > max(a, b) || a == 0 || b == 0) {
        return false;
    }
    ll cnt = max(1ll, (a - max(x, b)) / (2 * b));
    return solve(a - b * cnt, b, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int counter = 0;
    string ans = "";
    while(t-- > 0){
        counter ++;
        ll x, a, b;
        cin >> a >> b >> x;
        cout << (solve(a, b, x)? "YES\n" : "NO\n");
    }
    
    return 0;
}
