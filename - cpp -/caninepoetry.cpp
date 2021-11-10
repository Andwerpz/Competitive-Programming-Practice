
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1466C

//for each letter, just make sure it's not equal to to the two previous letters in the string. 

//if you need to change the letter, since you're only checking against 3 letters, and there are 26 letters in the alphabet, you don't need to change it to 
//a specific letter, you just need to know that you changed it.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int ans = 0;
        for(int i = 0; i < s.length(); i++){
            if(i >= 1 && s[i] != 0 && s[i - 1] == s[i]){
                ans ++;
                s[i] = 0;
            }
            else if(i >= 2 && s[i] != 0 && s[i - 2] == s[i]){
                ans ++;
                s[i] = 0;
            }
        }
        cout << ans << endl;
    }

    return 0;
}



