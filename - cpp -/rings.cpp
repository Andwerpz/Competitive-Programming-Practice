
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1562C

//10 submissions till right answer.. I don't think thats a record

//first, check if there is a zero in the second half. If there is a zero, you can have two substrings. The larger value one will be from the beginning to the first zero in 
//the second half, and the second one will be the same, minus the first zero. 

//if there is no zero in the second half, then take a look at the first half, and do essentially the same thing.

//if there is no zero at all, then you can have two equal substrings, 1 - (n - 1) and 2 - n.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        bool hasZero = false;
        int pointer = 0;
        for(int i = n / 2; i < n; i++){
            if(s[i] == '0'){
                hasZero = true;
                pointer = i + 1;
                break;
            }
        }
        if(hasZero){
            cout << "1 " << pointer << " 1 " << pointer - 1 << endl;
        }
        else{   //there is no zero in the second half
            for(int i = n - n / 2 - 1; i >= 0; i--){
                if(s[i] == '0'){
                    hasZero = true;
                    pointer = i + 1;
                    break;
                }
            }
            if(hasZero){
                cout << pointer << " " << n << " " << pointer + 1 << " " << n << endl;
            }
            else{   //there is no zero
                cout << "1 " << n - 1 << " " << "2 " << n << endl;
            }
        }
    }

    return 0;
}



