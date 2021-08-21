
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Palindrome Reorder

int main() {

    string s;
    cin >> s;
    vector<int> charCnt(26);
    for(int i = 0; i < s.length(); i++){
        charCnt[s[i] - 'A'] ++;
    }
    bool seenOdd = false;
    int oddIndex = -1;
    bool isValid = true;
    for(int i = 0; i < charCnt.size(); i++){
        if(charCnt[i] % 2 == 1){
            if(!seenOdd){
                seenOdd = true;
                oddIndex = i;
            }
            else {
                isValid = false;
                break;
            }
        
        }
    }
    if(isValid){
        for(int i = 0; i < 26; i++){
            for(int j = 0; j < charCnt[i] / 2; j++){
                cout << (char) (i + 'A');
            }
        }
        if(seenOdd){
            cout << (char) (oddIndex + 'A');
        }
        for(int i = 25; i >= 0; i--){
            for(int j = 0; j < charCnt[i] / 2; j++){
                cout << (char) (i + 'A');
            }
        }
    }
    else{
        cout << "NO SOLUTION\n";
    }
    
    return 0;
}


