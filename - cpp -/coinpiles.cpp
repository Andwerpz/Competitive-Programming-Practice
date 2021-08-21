
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Coin Piles

int main() {

    int t, a, b;
    cin >> t;
    while(t-- > 0){
        cin >> a >> b;
        if(a <= b){
            int temp = a;
            a = b;
            b = temp;
        }
        int diff = abs(a - b);
        a -= diff * 2;
        b -= diff;
        if(a < 0 || b < 0 || a % 3 != 0){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
        }
    }
    
    return 0;
}



