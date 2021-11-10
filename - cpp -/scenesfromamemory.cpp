
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1562B

//if there is a solution, then you must be able to do it in 2 digits or less. 

//first check through to see if there is a 1 digit solution.

//then go through all possible combinations of 2 digits. Since k is so small, we can do this.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 0;
    cin >> t;
    while(t-- > 0){
        int k = 0;
        cin >> k;
        string s;
        cin >> s;
        vector<int> digits(k);
        for(int i = 0; i < k; i++){
            digits[i] = s[i] - '0';
        }
        bool digitValid = false;
        for(int i = 0; i < k; i++){
            for(int j = 2; j <= 4; j++){
                if((digits[i] % j == 0 && digits[i] != j) || digits[i] == 1){
                    digitValid = true;
                    cout << "1\n" << digits[i] << endl;
                    goto outer;
                }
            }
        }
        outer:;
        if(!digitValid){
            for(int i = 0; i < k; i++){
                for(int j = i + 1; j < k; j++){
                    int next = digits[i] * 10 + digits[j];
                    for(int l = 2; l <= next / 2; l++){
                        if(next % l == 0){
                            cout << "2\n" << next << endl;
                            goto stop;
                        }
                    }
                }
            }
        }
        stop:;
    }

    return 0;
}



