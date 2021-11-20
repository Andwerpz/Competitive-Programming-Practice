
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1604D

//you just have to figure out how x and y behave under certain conditions. 

//if x == y, then n = x. This one is pretty obvious

//if x > y, then n = x + y. 
//you see that n % x will always increase when we add y, since y is guaranteed to be less than x. Also notice that n % x always equals y.
//also, y % n will always equal y, since n is going to be bigger than y.
//thus, n % x == y % n when n = x + y.

//if x < y, then n = (x + (y - x) - y % x + y) / 2. This one is pretty complicated
//this comes from the observation when x < y && x * 2 >= y, the answer is always going to be n = (x + y) / 2
//we just find the multiple of x that is closest to y to replace x for the general case.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll x, y;
        cin >> x >> y;
        if(x == y){
            cout << x << endl;
        }
        else if(x > y){
            cout << (x + y) << endl;
        }
        else {
            ll n = x;
            ll diff = y - x;
            diff /= x;
            n += diff * x;
            cout << (n + y) / 2 << endl;
        }
    }    

    return 0;
}
