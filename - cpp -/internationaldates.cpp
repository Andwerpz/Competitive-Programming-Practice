#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 B

//if the first date is greater than 12, then it's EU, if the second one is greater than 12, then it's US, 
//but if they're both not greater than 12, then it could be either. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int a, b;
    a = (s[0] - '0') * 10 + (s[1] - '0');
    b = (s[3] - '0') * 10 + (s[4] - '0');
    if(a <= 12 && b <= 12) {
        cout << "either\n";
    }
    else if(a > 12) {
        cout << "EU\n";
    }
    else {
        cout << "US\n";
    }
    
    return 0;
}
