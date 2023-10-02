#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - hissingmicrophone

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    bool isValid = false;
    for(int i = 1; i < s.size(); i++){
        if(s[i] == 's' && s[i - 1] == 's'){
            isValid = true;
        }
    }
    cout << (isValid? "hiss" : "no hiss") << "\n";
    
    return 0;
}
