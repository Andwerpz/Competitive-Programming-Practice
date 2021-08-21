
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 87A

//you can iterate the smaller number of (a, b) to lcm(a, b). This works since you only have to do a maximum of a iterations to get there, and a <= 10^6.

int main() {

    ll a, b;
    cin >> a >> b;
    bool reverse = false;
    if(a < b){
        reverse = true;
        ll temp = a;
        a = b;
        b = temp;
    }
    ll aAmt = 0;
    ll bAmt = 0;
    ll aPointer = 0;
    ll bPointer = 0;
    while(true){
        bPointer += b;
        ll prev = bPointer - b;
        if(aPointer + a <= bPointer && aPointer + a > prev){
            aPointer += a;
        }
        if(aPointer > prev){
            aAmt += aPointer - prev;
            bAmt += b - (aPointer - prev);
        }
        else{
            bAmt += b;
        }
        if(aPointer == bPointer){
            break;
        }
    }
    if(aAmt == bAmt){
        cout << "Equal\n";
    }
    else if(aAmt > bAmt){
        cout << (reverse? "Masha\n" : "Dasha\n");
    }
    else{
        cout << (reverse? "Dasha\n" : "Masha\n");
    }

    return 0;
}



