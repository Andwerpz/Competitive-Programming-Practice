
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1567A

//just copy the bottom row except for 'U' and 'D'. you flip those.

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
        string ans = "";
        for(int i = 0; i < n; i++){
            if(s[i] == 'U'){
                ans += 'D';
            }
            else if(s[i] == 'D'){
                ans += 'U';
            }
            else{
                ans += s[i];
            }
        }
        cout << ans << endl;
    }

    return 0;
}



