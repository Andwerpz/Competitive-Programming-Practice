
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//Codeforces - 1481A

int main() {

    int t;
    cin >> t;
    while(t-- > 0){
        int x, y;
        cin >> x >> y;
        string s;
        cin >> s;
        vector<int> moves(4);   //L, R, D, U
        for(int i = 0; i < s.length(); i++){
            char next = s[i];
            if(next == 'L'){
                moves[0] ++;
            }
            else if(next == 'R'){
                moves[1] ++;
            }
            else if(next == 'U'){
                moves[3] ++;
            }
            else {
                moves[2] ++;
            }
        }
        bool isValid = false;
        if(x <= 0 && moves[0] >= abs(x)){
            if(y <= 0 && moves[2] >= abs(y)){
                isValid = true;
            }
            else if(y >= 0 && moves[3] >= y){
                isValid = true;
            }
        }
        else if(x >= 0 && moves[1] >= x){
            if(y <= 0 && moves[2] >= abs(y)){
                isValid = true;
            }
            else if(y >= 0 && moves[3] >= y){
                isValid = true;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}



