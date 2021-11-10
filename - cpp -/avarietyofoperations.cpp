
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1556A

//first, if the average between c and d is not a whole number, then the input is invalid.

//else, then we can just make a and b both equal to the average, and then c and d will be the same distance from both.

//there are some other edge cases that you need to watch out for. If c == d, then the ans is 1. and if c == 0 and d == 0, then the ans is 0.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int c, d;
        cin >> c >> d;
        if(c == 0 && d == 0){
            cout << 0 << endl;
        }
        else if(c == d){
            cout << 1 << endl;
        }
        else if(abs(c - d) % 2 == 0){
            cout << 2 << endl;
        }
        else{
            cout << -1 << endl;
        }
    }

    return 0;
}



