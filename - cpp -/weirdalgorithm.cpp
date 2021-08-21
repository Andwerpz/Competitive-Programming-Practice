
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//CSES - Weird Algorithm

//simulation

int main()
{
    
    long long n;
    cin >> n;
    cout << n << " ";
    while(n != 1){
        if(n % 2 == 0){
            n /= 2;
        }
        else{
            n *= 3;
            n ++;
        }
        cout << n << " ";
    }

    return 0;
}



