
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1326A

//you can't have a number of length 1 be valid.

//all other numbers can take the form 233...333

//Since it is odd, it won't be divisible by 2, and we know that the sum of digits isn't divisible by 3, so it can't be divided by 3 either.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        if(n == 1){
            cout << "-1\n";
        }
        else{
            for(int i = 0; i < n; i++){
                cout << (i == 0? 2 : 3);
            }
            cout << endl;
        }
    }

    return 0;
}



