
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces 1567B

//since you know that you must include all numbers from 0 - (a - 1), first calculate that xor sum. Then in order to get the remaining xor sum that you need to make b,
//you can just xor the sum with b. 

//If the remaining xor sum is less than a, then you only need 1 extra number.

//if the sum is equal to a, then you need 2 extra numbers.

//if the sum is greater than a then you need only 1 extra number

//if the sum is equal to 0, then you need no extra numbers.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    vector<int> pfx(300010);
    for(int i = 1; i < pfx.size(); i++){
        pfx[i] = pfx[i - 1] ^ i;
    }
    while(t-- > 0){
        int a, b;
        cin >> a >> b;
        int aXor = pfx[a - 1];
        int bXor = b ^ aXor;
        if(bXor == a){
            cout << (a + 2) << endl;
        }
        else{
            if(bXor == 0){
                cout << a << endl;
            }
            else{
                cout << (a + 1) << endl;
            }
        }
    }

    return 0;
}



