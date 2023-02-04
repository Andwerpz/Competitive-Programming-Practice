#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 H

//bruh, the problem statement says that the troll already ran from one bridge, so the 
//number of bridges needed to be searched is b - 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int b, k, g;
    cin >> b >> k >> g;
    int nGroups = k / g;
    int d = (b - 1) / nGroups + ((b - 1) % nGroups == 0? 0 : 1);
    cout << d << "\n";
    
    return 0;
}
