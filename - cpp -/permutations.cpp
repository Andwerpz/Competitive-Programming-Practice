
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES - Permutations

int main()
{

    int n;
    cin >> n;
    if(n == 1){
        cout << n;
    }
    else if(n <= 3){
        cout << "NO SOLUTION\n";
    }
    else{
        int r = n / 2 + 1;
        for(int i = 1; i <= n / 2; i++){
            cout << r << " " << i << " ";
            r ++;
        }
        if(r <= n){
            cout << r;
        }
        cout << "\n";
    }

    return 0;
}



