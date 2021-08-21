
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//Codeforces - 1379A

//just brute force through all the solutions.

int main() {

    int t, n;
    cin >> t;
    string x = "abacaba";
    while(t-- > 0){
        cin >> n;
        string s;
        cin >> s;
        bool isValid = false;
        for(int i = n - 7; i >= 0; i--){
            bool curValid = true;
            string cur;
            for(int j = 0; j < s.length(); j++){
                cur.push_back(s[j]);
            }
            //cout << cur << endl;
            for(int j = i; j < i + 7; j++){
                if(x[j - i] != s[j]){
                    if(s[j] == '?'){
                        cur[j] = x[j - i];
                    }
                    else{
                        curValid = false;
                        break;
                    }
                }
            }
            if(curValid){
                //cout << "YES\n";
                for(int j = 0; j <= n - 7; j++){
                    bool nowValid = true;
                    if(j != i){
                        for(int k = j; k < j + 7; k++){
                            if(x[k - j] != cur[k]){
                                if(cur[k] == '?'){
                                    cur[k] = 'x';
                                }
                                nowValid = false;
                            }
                        }
                        if(nowValid){
                            curValid = false;
                            break;
                        }
                    }
                    
                }
            }
            if(curValid){
                isValid = true;
                cout << "Yes\n" << cur << endl;
                break;
            }
        }
        if(!isValid){
            cout << "No\n";
        }
    }

    return 0;
}



