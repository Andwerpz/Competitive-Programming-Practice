
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1494A

using namespace std;

bool isValid1(string s, char a, char b, char c){    //a and b are '('
    int leftCount = 0;
    int rightCount = 0;
    bool isValid = true;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){
            leftCount ++;
        }
        else{
            rightCount ++;
        }
        if(leftCount > rightCount){
            isValid = false;
            break;
        }
    }
    if(isValid && leftCount == rightCount){
        return true;
    }
    isValid = true;
    rightCount = 0;
    leftCount = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == c){
            rightCount ++;
        }
        else{
            leftCount ++;
        }
        if(leftCount > rightCount){
            isValid = false;
            break;
        }
    }
    if(isValid && leftCount == rightCount){
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        cout << ((isValid1(s, 'A', 'B', 'C') || isValid1(s, 'A', 'C', 'B') || isValid1(s, 'C', 'B', 'A'))? "YES\n" : "NO\n");
    }

    return 0;
}



