
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1566B

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        vector<int> groups;
        char prev = 0;
        bool seenZero = false;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '0'){
                seenZero = true;
            }
            if(s[i] != prev){
                groups.push_back(1);
                prev = s[i];
            }
            else{
                groups[groups.size() - 1] ++;
            }
        }
        //cout << groups.size() << endl;;
        if(groups.size() == 1){
            cout << (seenZero? "1\n" : "0\n");
        }
        else if(groups.size() == 2){
            cout << "1\n";
        }
        else if(groups.size() == 3 && s[0] == '1'){
            cout << "1\n";
        }
        else{
            cout << "2\n";
        }
    }

    return 0;
}



