#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - fyi

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    if(s[0] == '5' && s[1] == '5' && s[2] == '5') {
        cout << "1\n";
    }
    else {
        cout << "0\n";
    }
    
    return 0;
}
