#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1796B

//if a and b share a common first or last character, then you can generate a template string, t, of length 2 where
//one character is an asterisk, and the other is the first or last character, whichever is common between a and b. 

//else, you need to look for a substring of length 2 that is common between a and b. If a substring, c, of length 
//2 exists that is common between a and b, then you can create a template of the form *c*. Notice that c can be longer than 2, 
//but cannot be shorter than 2 since the number of asterisks must be less than or equal to the number of non-asterisks. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string a, b;
        cin >> a >> b;
        if(a[0] == b[0]){
            cout << "YES\n";
            cout << a[0] << "*\n";
            continue;
        }
        if(a[a.size() - 1] == b[b.size() - 1]) {
            cout << "YES\n";
            cout << "*" << a[a.size() - 1] << "\n";
            continue;
        }
        bool isValid = false;
        string ans = "";
        for(int i = 0; i < a.size() - 1; i++){
            for(int j = 0; j < b.size() - 1; j++){
                if(a.substr(i, 2) == b.substr(j, 2)) {
                    isValid = true;
                    ans = a.substr(i, 2);
                }
            }
        }
        if(isValid) {
            cout << "YES\n";
            cout << "*" << ans << "*" << "\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
