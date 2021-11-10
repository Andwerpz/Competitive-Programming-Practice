
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1480A

//just minimize or maximize each letter in turn.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                if(s[i] == 'a'){
                    s[i] = 'b';
                }
                else{
                    s[i] = 'a';
                }
            }
            else{
                if(s[i] == 'z'){
                    s[i] = 'y';
                }
                else{
                    s[i] = 'z';
                }
            }
        }
        cout << s << endl;
    }

    return 0;
}



