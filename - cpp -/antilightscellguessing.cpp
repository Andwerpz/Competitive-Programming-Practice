
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1610A

//you just have to check for a few cases:

//if n, m == 1: then there is only 1 cell available, so k = 0.
//if n == 1 || m == 1: you can guess one cell at either end, so k = 1.
//else: guess at two corners on the same side. k = 2

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        if(n == 1 && m == 1){
            cout << "0\n";
        }
        else if(n == 1 || m == 1){
            cout << "1\n";
        }
        else{
            cout << "2\n";
        }
    }
    
    return 0;
}
