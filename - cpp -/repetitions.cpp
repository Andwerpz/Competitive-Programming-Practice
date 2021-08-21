
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//CSES - Repetitions

int main()
{

    string s;
    cin >> s;
    int ans = 0;
    char prev;
    int cur = 0;
    for(int i = 0; i < s.length(); i++){
        if(i == 0){
            prev = s[0];
        }
        if(prev != s[i]){
            prev = s[i];
            cur = 0;
        }
        cur ++;
        ans = max(cur, ans);
    }
    cout << ans;
    
    return 0;
}



